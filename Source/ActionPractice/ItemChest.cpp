// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemChest.h"

void AItemChest::Interact_Implementation(APawn* InstigatorPawn)
{
	LidMesh->SetRelativeRotation(FRotator(TargetPitch,0,0));
}

// Sets default values
AItemChest::AItemChest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Basemesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	RootComponent = Basemesh;

	LidMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LidMesh"));
	LidMesh->SetupAttachment(Basemesh);

	TargetPitch = 110;
}

// Called when the game starts or when spawned
void AItemChest::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AItemChest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

