// Fill out your copyright notice in the Description page of Project Settings.


#include "AICharacter.h"
#include <Perception/PawnSensingComponent.h>
#include <AIController.h>
#include <BehaviorTree/BlackboardComponent.h>
#include "ActionCharacter.h"
#include "AttributeComponent.h"
#include "ActionAIController.h"
#include "BrainComponent.h"
#include "Components/MeshComponent.h"
#include "ActionUserWidget.h"
// Sets default values
AAICharacter::AAICharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;

	SensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComp"));
	AttributeComp = CreateDefaultSubobject< UAttributeComponent>(TEXT("HealthComp"));

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	TimeToHitParamName = "GameTime";
}

void AAICharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	SensingComp->OnSeePawn.AddDynamic(this, &AAICharacter::OnPawnSeen);
	AttributeComp->OnHealthChanged.AddDynamic(this, &AAICharacter::OnHealthChanged);
}


void AAICharacter::SetTargetActor(AActor* Actor)
{
	AActionCharacter* Player = Cast<AActionCharacter>(Actor);
	if (Player == nullptr) return;
	AAIController* AIC = Cast<AAIController>(GetController());
	if (AIC)
	{
		UBlackboardComponent* BBComp = AIC->GetBlackboardComponent();

		BBComp->SetValueAsObject("TargetActor", Actor);
	}
}

void AAICharacter::OnPawnSeen(APawn* Pawn)
{
	SetTargetActor(Pawn);
	DrawDebugString(GetWorld(), GetActorLocation(), "Player Spotted", nullptr, FColor::White, 4.0f, true);
}

void AAICharacter::OnHealthChanged(AActor* InstigatorActor, UAttributeComponent* OwningComp, float NewHealth, float Delta)
{
	if (Delta < 0.0f)
	{
		if (InstigatorActor != this)
		{
			SetTargetActor(InstigatorActor);
		}
		if (ActiveHealthBar == nullptr)
		{
			ActiveHealthBar = CreateWidget<UActionUserWidget>(GetWorld(), HealthBarWidget);

			if (ActiveHealthBar)
			{
				ActiveHealthBar->AttachedActor = this;
				ActiveHealthBar->AddToViewport();
			}
		}

		GetMesh()->SetScalarParameterValueOnMaterials(TimeToHitParamName, GetWorld()->TimeSeconds);
		if (NewHealth <= 0.0f)
		{
			// stop BT
			AActionAIController* AIC = Cast<AActionAIController>(GetController());
			if (AIC)
			{
				AIC->GetBrainComponent()->StopLogic("Killed");
			}
			// ragdoll
			GetMesh()->SetAllBodiesSimulatePhysics(true);
			GetMesh()->SetCollisionProfileName("Ragdoll");

			// set lifespan
			SetLifeSpan(10.0f);
		}
	}

}

