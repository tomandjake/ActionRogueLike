// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "HUD/HUDEventDispatcher.h"
#include "ActionGameModeBase.generated.h"

/**
 * 
 */
class UEnvQueryInstanceBlueprintWrapper;
class UCurveFloat;
class UEnvQuery;

UCLASS()
class ACTIONPRACTICE_API AActionGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
protected:

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	UEnvQuery* SpawnBotQuery;

	UPROPERTY(EditAnywhere, Category = "AI")
	UCurveFloat* DiffcultyCurve;

	UPROPERTY()
	
	
	FTimerHandle TimerHandle_SpawnBots;
	
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	float SpawnTimerInterval;

	UPROPERTY(EditAnywhere, Category = "AI")
	TSubclassOf<AActor> MinionClass;

	UFUNCTION()
	void SpawnBotTimerElapsed();


	UFUNCTION()
	void OnQueryCompleted(UEnvQueryInstanceBlueprintWrapper* QueryInstance, EEnvQueryStatus::Type QueryStatus);

	UFUNCTION()
	void RespawnPlayerElapsed(AController* Controller);
public:
	virtual void OnActorKilled(AActor* VictimActor, AActor* Killer);

	AActionGameModeBase();
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)override;
	virtual void StartPlay() override;
	
	UPROPERTY()
	AHUDEventDispatcher* HUDEventDispatcher;
};
