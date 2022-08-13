// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"

void AActionAIController::BeginPlay()
{
	Super::BeginPlay();

	if (ensureMsgf(BehaviorTree, TEXT("Behaviro is nullptr.")))
	{
		RunBehaviorTree(BehaviorTree);
	}

	//APawn* MyPawn = UGameplayStatics::GetPlayerPawn(this, 0);
	//if (MyPawn)
	//{
	//	GetBlackboardComponent()->SetValueAsObject("TargetActor", MyPawn);
	//}
}
