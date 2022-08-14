// Fill out your copyright notice in the Description page of Project Settings.


#include "Action.h"

void UAction::StartAction_Implementation(AActor* Instigator)
{
	UE_LOG(LogTemp, Log, TEXT("Running: %s"), *GetNameSafe(this));


}

void UAction::StopAction_Implementation(AActor* Instigator)
{
	UE_LOG(LogTemp, Log, TEXT("Stoping: % s"), *GetNameSafe(this));


}
