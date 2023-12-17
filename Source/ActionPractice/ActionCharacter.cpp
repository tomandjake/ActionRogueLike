// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include <GameFramework/CharacterMovementComponent.h>
#include "InteractionComponent.h"
#include "AttributeComponent.h"
#include "ActionComponent.h"
#include "ActionGameModeBase.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

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
	InteractionComp = CreateDefaultSubobject<UInteractionComponent>(TEXT("InteractionComp"));

	AttributeComp = CreateDefaultSubobject<UAttributeComponent>(TEXT("AttributeComp"));
	ActionComp = CreateDefaultSubobject<UActionComponent>(TEXT("ActionComp"));

	GetCharacterMovement()->bOrientRotationToMovement = true;
	bUseControllerRotationYaw = false;
}

void AActionCharacter::HealSelf(float Amout /* = 100*/)
{
	AttributeComp->ApplyHealthChange(this, Amout);
}

void AActionCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	AttributeComp->OnHealthChanged.AddDynamic(this, &AActionCharacter::OnHealthChanged);
	OnKillEventHandle.AddDynamic(this, &AActionCharacter::OnKillEvent);
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
	PlayerInputComponent->BindAction("PrimaryInteract", IE_Pressed, this, &AActionCharacter::PrimaryInteract);

	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AActionCharacter::SprintStart);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &AActionCharacter::SprintStop);
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
	PlayAnimMontage(AttackAnim);

	FRotator Rotator = GetControlRotation();
	SetActorRotation(Rotator);
	GetWorldTimerManager().SetTimer(Timerhandle_PrimaryAttack,this,&AActionCharacter::PrimaryAttack_TimeElapsed, 0.1f);
	//GetWorldTimerManager().ClearTimer(Timerhandle_PrimaryAttack);
}

void AActionCharacter::PrimaryInteract()
{
	if (InteractionComp == nullptr)
	{
		return;
	}
	InteractionComp->PrimaryInteract();
}

void AActionCharacter::PrimaryAttack_TimeElapsed()
{
	if (ensure(ProjectileClass))
	{
		FVector HandLocation = GetMesh()->GetSocketLocation("Muzzle_01");
		FTransform SpawnTM = FTransform(GetControlRotation(), HandLocation);

		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParams.Instigator = this;

		auto Projectile = GetWorld()->SpawnActorDeferred<AActor>(ProjectileClass, SpawnTM,this,this, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
		auto MovementComp = Cast<UProjectileMovementComponent>(Projectile->GetComponentByClass(ProjectileMovementClass));
		if (MovementComp)
		{
			MovementComp->InitialSpeed = 10000.0f;
		}
		UGameplayStatics::FinishSpawningActor(Projectile, SpawnTM);
	}
}

void AActionCharacter::SprintStart()
{
	ActionComp->StartActionByName(this, "Sprint");
}

void AActionCharacter::SprintStop()
{
	ActionComp->StopActionByName(this, "Sprint");
}

void AActionCharacter::OnHealthChanged(AActor* InstigatorActor, UAttributeComponent* OwningComp, float NewHealth, float Delta)
{
	if (NewHealth <= 0.0f && Delta < 0.0f)
	{

		APlayerController* PC = Cast<APlayerController>(GetController());
		DisableInput(PC);
	}
}
void AActionCharacter::OnKillEvent()
{
	ComboKillNum ++;


	AActionGameModeBase* GameMode = Cast<AActionGameModeBase>(GetWorld()->GetAuthGameMode());
	if(GameMode)
	{
		GameMode->HUDEventDispatcher->BroadcastOnKillEvent(ComboKillNum);
	}
	
	if(KillTimerHandle.IsValid())
	{
		GetWorld()->GetTimerManager().ClearTimer(KillTimerHandle);
	}
	GetWorld()->GetTimerManager().SetTimer(KillTimerHandle, [this]()
	{
		ComboKillNum = 0;
	},3.0f,false);
}


