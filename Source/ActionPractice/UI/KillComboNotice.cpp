// Fill out your copyright notice in the Description page of Project Settings.


#include "KillComboNotice.h"

#include "ActionPractice/ActionGameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "Components/WidgetSwitcher.h"
#include "GameFramework/GameModeBase.h"

void UKillComboNotice::NativeConstruct()
{
	Super::NativeConstruct();
	// bind to event
	auto GameMode = Cast<AActionGameModeBase>(GetWorld()->GetAuthGameMode());
	if(GameMode)
	{
		AHUDEventDispatcher* EventDispatcher = GameMode->HUDEventDispatcher;
		if(EventDispatcher)
		{
			EventDispatcher->OnKillEvent.AddDynamic(this, &UKillComboNotice::UpdateNotice);
		}
	}
}

void UKillComboNotice::UpdateNotice(int32 KillNum)
{
	if(KillNum>0 && KillNum <= 3)
	{
		if(TimerHandle.IsValid())
		{
			GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
		}
		KillNumSwitcher->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		KillNumSwitcher->SetActiveWidgetIndex(KillNum - 1);
		auto CallBack = [this]()
		{
			KillNumSwitcher->SetVisibility(ESlateVisibility::Hidden);
		};
		GetWorld()->GetTimerManager().SetTimer(TimerHandle,CallBack,1.5,false);
	}
}
