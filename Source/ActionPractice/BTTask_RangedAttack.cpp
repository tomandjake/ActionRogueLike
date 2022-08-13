// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_RangedAttack.h"
#include "AIController.h"
#include "GameFramework/Character.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AttributeComponent.h"


UBTTask_RangedAttack::UBTTask_RangedAttack()
{
	MaxBulletSpreat = 8.0f;
}


EBTNodeResult::Type UBTTask_RangedAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* Mycontroller = OwnerComp.GetAIOwner();
	if (Mycontroller == nullptr) return EBTNodeResult::Failed;
	ACharacter* MyPawn = Cast<ACharacter>(Mycontroller->GetPawn());
	FVector MuzzleLocation = MyPawn->GetMesh()->GetSocketLocation("Muzzle_01");

	AActor* TargetActor = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("TargetActor"));
	if (TargetActor == nullptr) return EBTNodeResult::Failed;

	if (!UAttributeComponent::IsActorAlive(TargetActor))
	{
		return EBTNodeResult::Failed;
	}

	FVector Direction = TargetActor->GetActorLocation() - MuzzleLocation;
	FRotator MuzzleRotation = Direction.Rotation();

	MuzzleRotation.Pitch += FMath::RandRange(-MaxBulletSpreat, MaxBulletSpreat);
	MuzzleRotation.Yaw += FMath::RandRange(-MaxBulletSpreat, MaxBulletSpreat);

	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	Params.Instigator = MyPawn;
	AActor* NewProj = GetWorld()->SpawnActor<AActor>(ProjectileClass, MuzzleLocation, MuzzleRotation, Params);

	return NewProj ? EBTNodeResult::Succeeded : EBTNodeResult::Failed;
}
