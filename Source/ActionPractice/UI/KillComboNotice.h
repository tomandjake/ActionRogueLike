// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "KillComboNotice.generated.h"

/**
 * 
 */

class UWidgetSwitcher;
class UImage;

struct my_struct
{
	
};

FTimerHandle;

UCLASS()
class ACTIONPRACTICE_API UKillComboNotice : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
	UWidgetSwitcher* KillNumSwitcher;
	
	UPROPERTY(meta = (BindWidget))
	UImage* Image_1;
	
	UPROPERTY(meta = (BindWidget))
	UImage* Image_2;
	
	UPROPERTY(meta = (BindWidget))
	UImage* Image_3;

	FTimerHandle TimerHandle;

	virtual void NativeConstruct() override;
	
	UFUNCTION()
	void UpdateNotice(int32 KillNum);
};
