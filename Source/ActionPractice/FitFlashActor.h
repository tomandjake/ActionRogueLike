// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FitFlashActor.generated.h"

UCLASS()
class ACTIONPRACTICE_API AFitFlashActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFitFlashActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* StaticMeshComp;
	UPROPERTY(VisibleAnywhere)
	class UAttributeComponent* AttributeComp;
	
	UFUNCTION()
	void OnHealthChanged(AActor* InstigatorActor, UAttributeComponent* OwningComp, float NewHealth, float Delta);
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
