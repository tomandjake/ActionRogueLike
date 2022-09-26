// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDEventDispatcher.h"

// Sets default values
AHUDEventDispatcher::AHUDEventDispatcher()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
}

// Called when the game starts or when spawned
void AHUDEventDispatcher::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHUDEventDispatcher::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHUDEventDispatcher::BroadcastOnKillEvent(int32 KillNum)const
{
	OnKillEvent.Broadcast(KillNum);
}

