// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionGameModeBase.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "EnvironmentQuery/EnvQueryManager.h"
#include "AICharacter.h"
#include "EngineUtils.h"
#include "AttributeComponent.h"
#include "EnvironmentQuery/EnvQueryInstanceBlueprintWrapper.h"



AActionGameModeBase::AActionGameModeBase()
{
	SpawnTimerInterval = 2.0f;
}

void AActionGameModeBase::StartPlay()
{
	Super::StartPlay();

	GetWorldTimerManager().SetTimer(TimerHandle_SpawnBots, this, &AActionGameModeBase::SpawnBotTimerElapsed, SpawnTimerInterval, true);
}


void AActionGameModeBase::SpawnBotTimerElapsed()
{
	int NumOfAliveBots = 0;
	for (TActorIterator<AAICharacter> It(GetWorld()); It; ++It)
	{
		AAICharacter* Bot = *It;
		if (Bot == nullptr) continue;
		UAttributeComponent* HealthComp = Cast<UAttributeComponent>(Bot->GetComponentByClass(UAttributeComponent::StaticClass()));
		if (HealthComp && HealthComp->IsAlive())
		{
			NumOfAliveBots++;
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("Find %d alive bots."), NumOfAliveBots);

	int32 MaxBotCount = 10;

	if (DiffcultyCurve)
	{
		MaxBotCount = DiffcultyCurve->GetFloatValue(GetWorld()->TimeSeconds);
	}

	if (NumOfAliveBots >= MaxBotCount)
	{
		return;
	}

	UEnvQueryInstanceBlueprintWrapper* QueryInstance = UEnvQueryManager::RunEQSQuery(this, SpawnBotQuery, this, EEnvQueryRunMode::RandomBest5Pct, nullptr);
	if (ensure(QueryInstance))
	{
		QueryInstance->GetOnQueryFinishedEvent().AddDynamic(this, &AActionGameModeBase::OnQueryCompleted);
	}
}

void AActionGameModeBase::OnQueryCompleted(UEnvQueryInstanceBlueprintWrapper* QueryInstance, EEnvQueryStatus::Type QueryStatus)
{
	if (QueryStatus != EEnvQueryStatus::Success) 
	{
		UE_LOG(LogTemp, Warning, TEXT("Spawn bot EQS Query Faild!"));
		return;
	}

	TArray<FVector> Locations = QueryInstance->GetResultsAsLocations();
	if (Locations.IsValidIndex(0))
	{
		FVector CurLocation = Locations[0];
		CurLocation.Z += 100;
		GetWorld()->SpawnActor<AActor>(MinionClass, CurLocation, FRotator::ZeroRotator);
	}
}
