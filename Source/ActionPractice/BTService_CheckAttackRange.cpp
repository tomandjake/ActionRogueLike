// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_CheckAttackRange.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

void UBTService_CheckAttackRange::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	UBlackboardComponent* BlackBoardComp = OwnerComp.GetBlackboardComponent();
	if (BlackBoardComp == nullptr) return;
	AActor* TargetActor = Cast<AActor>(BlackBoardComp->GetValueAsObject("TargetActor"));
	if (TargetActor == nullptr) return;
	AAIController* MyController = OwnerComp.GetAIOwner();
	if (MyController == nullptr) return;
	APawn* MyPawn = MyController->GetPawn();
	if (MyPawn == nullptr) return;
	
	float Distance = FVector::Distance(TargetActor->GetActorLocation(), MyPawn->GetActorLocation());

	bool bWithinRange = Distance < 1000.f;

	bool bHasLOS = false;
	if (bWithinRange)
	{
		bHasLOS = MyController->LineOfSightTo(TargetActor);
	}

	BlackBoardComp->SetValueAsBool(AttackRangeKey.SelectedKeyName, bWithinRange && bHasLOS);
	UE_LOG(LogTemp, Warning, TEXT("bWithinRange && bHasLOS: %d"), bWithinRange && bHasLOS);
}
