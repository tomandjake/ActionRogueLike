// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include <GameFramework/CharacterMovementComponent.h>

// Sets default values
AActionCharacter::AActionCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComp->bUsePawnControlRotation = true;
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComp->SetupAttachment(SpringArmComp);
	SpringArmComp->SetupAttachment(RootComponent);

	GetCharacterMovement()->bOrientRotationToMovement = true;
	bUseControllerRotationYaw = false;
}

// Called when the game starts or when spawned
void AActionCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AActionCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AActionCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAxis("MoveForward", this, &AActionCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AActionCharacter::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);

	PlayerInputComponent->BindAction("PrimaryAttack", IE_Pressed, this, &AActionCharacter::PrimaryAttack);
}

void AActionCharacter::MoveForward(float value)
{
	FRotator ControllerRot = GetControlRotation();
	ControllerRot.Pitch = 0.0f;
	ControllerRot.Roll = 0.0f;
	//UE_LOG(LogTemp, Warning, TEXT("%f %f %f"), ControllerRot.Vector().X, ControllerRot.Vector().Y, ControllerRot.Vector().Z);
	AddMovementInput(ControllerRot.Vector(), value);
}

void AActionCharacter::MoveRight(float value)
{
	FRotator ControllerRot = GetControlRotation();
	ControllerRot.Pitch = 0.0f;
	ControllerRot.Roll = 0.0f;
	FVector RightVector = FRotationMatrix(ControllerRot).GetScaledAxis(EAxis::Y);

	AddMovementInput(RightVector, value);
}

void AActionCharacter::PrimaryAttack()
{
	FVector HandLocation = GetMesh()->GetSocketLocation("Muzzle_01");
	FTransform SpawnTM = FTransform(GetControlRotation(), HandLocation);

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTM, SpawnParams);
}

