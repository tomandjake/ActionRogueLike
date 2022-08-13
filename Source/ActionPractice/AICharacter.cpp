// Fill out your copyright notice in the Description page of Project Settings.


#include "AICharacter.h"
#include <Perception/PawnSensingComponent.h>
#include <AIController.h>
#include <BehaviorTree/BlackboardComponent.h>
#include "ActionCharacter.h"

// Sets default values
AAICharacter::AAICharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;

	SensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComp"));

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void AAICharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	SensingComp->OnSeePawn.AddDynamic(this, &AAICharacter::OnPawnSeen);
}

void AAICharacter::OnPawnSeen(APawn* Pawn)
{
	AActionCharacter* Player = Cast<AActionCharacter>(Pawn);
	if (Player == nullptr) return;
	AAIController* AIC = Cast<AAIController>(GetController());
	if (AIC)
	{
		UBlackboardComponent* BBComp = AIC->GetBlackboardComponent();

		BBComp->SetValueAsObject("TargetActor", Pawn);

		DrawDebugString(GetWorld(), GetActorLocation(), "Player Spotted", nullptr, FColor::White, 4.0f, true);
	}
}

