// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ActionUserWidget.generated.h"

/**
 * 
 */

class USizeBox;

UCLASS()
class ACTIONPRACTICE_API UActionUserWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
	USizeBox* ParentSizeBox;
	
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime)override;

	UPROPERTY(BlueprintReadOnly, Category = "UI")
	AActor*	AttackedActor;
	
};
