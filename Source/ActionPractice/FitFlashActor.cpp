// Fill out your copyright notice in the Description page of Project Settings.


#include "FitFlashActor.h"
#include "AttributeComponent.h"

// Sets default values
AFitFlashActor::AFitFlashActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("Static Mesh");
	AttributeComp = CreateDefaultSubobject<UAttributeComponent>("Attribute Comp");
	RootComponent = StaticMeshComp;
	AttributeComp->OnHealthChanged.AddUniqueDynamic(this, &AFitFlashActor::OnHealthChanged);
}

// Called when the game starts or when spawned
void AFitFlashActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AFitFlashActor::OnHealthChanged(AActor* InstigatorActor, UAttributeComponent* OwningComp, float NewHealth, float Delta)
{
	if (Delta < 0.0f)
	{
		StaticMeshComp->SetScalarParameterValueOnMaterials("GameTime", GetWorld()->TimeSeconds);
	}
}

// Called every frame
void AFitFlashActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


