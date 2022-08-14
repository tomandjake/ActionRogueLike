// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionComponent.h"
#include "Action.h"

// Sets default values for this component's properties
UActionComponent::UActionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UActionComponent::AddAction(AActor* Instigator, TSubclassOf<UAction> ActionClass)
{
	if (!ensure(ActionClass))
	{
		return;
	}

	UAction* NewAction = NewObject<UAction>(GetOwner(), ActionClass);
	if (ensure(NewAction))
	{
		Actions.Add(NewAction);
	}
}

bool UActionComponent::StartActionByName(AActor* Instigator, FName ActionName)
{
	//SCOPE_CYCLE_COUNTER(STAT_StartActionByName);

	for (UAction* Action : Actions)
	{
		if (Action && Action->ActionName == ActionName)
		{
			//if (!Action->CanStart(Instigator))
			//{
			//	FString FailedMsg = FString::Printf(TEXT("Failed to run: %s"), *ActionName.ToString());
			//	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FailedMsg);
			//	continue;
			//}

			//// Is Client?
			//if (!GetOwner()->HasAuthority())
			//{
			//	ServerStartAction(Instigator, ActionName);
			//}

			// Bookmark for Unreal Insights
			//TRACE_BOOKMARK(TEXT("StartAction::%s"), *GetNameSafe(Action));

			Action->StartAction(Instigator);
			return true;
		}
	}

	return false;
}


bool UActionComponent::StopActionByName(AActor* Instigator, FName ActionName)
{
	for (UAction* Action : Actions)
	{
		if (Action && Action->ActionName == ActionName)
		{
			Action->StopAction(Instigator);
			return true;
		}
	}

	return false;
}

// Called when the game starts
void UActionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UActionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

