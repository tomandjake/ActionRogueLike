// Fill out your copyright notice in the Description page of Project Settings.


#include "TestSettlement.h"

// Sets default values
ATestSettlement::ATestSettlement()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATestSettlement::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATestSettlement::ClientTravle(AActionCharacter* Character)
{
	if(!Character) return;
	auto Controller = Character->GetController();
	auto PlayerController = Cast<APlayerController>(Controller);
	PlayerController->ClientTravel("/Game/Maps/2DSettlement",ETravelType::TRAVEL_Absolute, false);
}

// Called every frame
void ATestSettlement::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

