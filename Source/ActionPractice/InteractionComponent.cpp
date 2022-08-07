// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractionComponent.h"
#include "GamePlayInterface.h"

// Sets default values for this component's properties
UInteractionComponent::UInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UInteractionComponent::PrimaryInteract()
{
	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);
	AActor* MyOwner = GetOwner();
	FVector Start;
	FVector End;

	FVector EyeLocation;
	FRotator EyeRotation;
	MyOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);
	Start = EyeLocation;
	End = EyeLocation + (EyeRotation.Vector() * 500);

	//FHitResult Hit; 
	//bool bBlockingHit =	GetWorld()->LineTraceSingleByObjectType(Hit, Start, End, ObjectQueryParams);

	TArray<FHitResult> Hits;
	FCollisionShape Shape;
	float Radius = 30.0f;
	Shape.SetSphere(Radius);
	bool bBlockingHit = GetWorld()->SweepMultiByObjectType(Hits, Start, End,FQuat::Identity, ObjectQueryParams, Shape);
	FColor LineColor = bBlockingHit ? FColor::Green : FColor::Blue;

	for (FHitResult Hit : Hits)
	{
		AActor* HitActor = Hit.GetActor();
		if (HitActor)
		{
			//UE_LOG(LogTemp, Warning, TEXT("okkkkkkk"));
			FString Name = HitActor->GetName();
			//UE_LOG(LogTemp, Warning, TEXT("Actor name:%s"),*Name);
			if (HitActor->Implements<UGamePlayInterface>())
			{
				//UE_LOG(LogTemp, Warning, TEXT("okkkkkkk"));
				APawn* MyPawn = Cast<APawn>(MyOwner);
				IGamePlayInterface::Execute_Interact(HitActor, MyPawn);
				break;
			}
		}
		DrawDebugSphere(GetWorld(), Hit.ImpactPoint, Radius, 32, LineColor, false, 2.0f);
	}

	//if (AActor* HitActor = Hit.GetActor())
	//{	
	//	if (HitActor->Implements<UGamePlayInterface>())
	//	{
	//		APawn* MyPawn = Cast<APawn>(MyOwner);
	//		IGamePlayInterface::Execute_Interact(HitActor, MyPawn); 
	//	}
	//}

	DrawDebugLine(GetWorld(), Start, End, FColor::Blue, false, 2.0f, 0.f, 2.0f);
}
