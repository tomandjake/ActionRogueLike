// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ActionCharacter.generated.h"

UCLASS()
class ACTIONPRACTICE_API AActionCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AActionCharacter();

	UFUNCTION(Exec)
	void HealSelf(float Amout=100);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, Category = "Attack")
	TSubclassOf<AActor> ProjectileClass;
	UPROPERTY(EditAnywhere, Category = "Attack")
	UAnimMontage* AttackAnim;

	FTimerHandle Timerhandle_PrimaryAttack;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Locomotion")
		float ForwardSpeed = 50;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		class UAttributeComponent* AttributeComp;
private:
	UPROPERTY(VisibleAnywhere)
		class UCameraComponent* CameraComp;
	UPROPERTY(VisibleAnywhere)
		class USpringArmComponent* SpringArmComp;
	UPROPERTY(VisibleAnywhere)
		class UInteractionComponent* InteractionComp;

	void MoveForward(float value);
	void MoveRight(float value);
	void PrimaryAttack();
	void PrimaryInteract();
	void PrimaryAttack_TimeElapsed();

	UFUNCTION()
	void OnHealthChanged(AActor* InstigatorActor, UAttributeComponent* OwningComp, float NewHealth, float Delta);

	virtual void PostInitializeComponents() override;

};
