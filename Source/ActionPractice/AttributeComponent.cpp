// Fill out your copyright notice in the Description page of Project Settings.


#include "AttributeComponent.h"
#include "ActionGameModeBase.h"

static TAutoConsoleVariable<float> CVarDamageMultiplier(TEXT("su.DamageMultiplier"), 1.0f, TEXT("Global Damage Modifier for Attribute Component."), ECVF_Cheat);

// Sets default values for this component's properties
UAttributeComponent::UAttributeComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	MaxHealth = 100;
	Health = MaxHealth;
}


bool UAttributeComponent::IsAlive() const
{
	return Health > 0.0f;
}

bool UAttributeComponent::ApplyHealthChange(AActor* Instigator,float Delta)
{
	if (!GetOwner()->CanBeDamaged())
	{
		return false;
	}
	float OldHealth = Health;
	if (Delta < 0.0f)
	{
		float DamageMultiplier = CVarDamageMultiplier.GetValueOnGameThread();

		Delta *= DamageMultiplier;
	}

	Health = FMath::Clamp(Health + Delta, 0.0f, MaxHealth);

	float ActualDelta = Health - OldHealth;
	OnHealthChanged.Broadcast(Instigator, nullptr, Health, Delta);

	if (Delta < 0.0f && Health <= 0.0f)
	{
		AActionGameModeBase* GM = GetWorld()->GetAuthGameMode<AActionGameModeBase>();
		if (GM)
		{
			GM->OnActorKilled(GetOwner(), Instigator);
		}
	}

	return ActualDelta != 0;
}

UAttributeComponent* UAttributeComponent::GetAttribute(AActor* FromActor)
{
	if (FromActor)
	{
		return Cast<UAttributeComponent>(FromActor->GetComponentByClass(UAttributeComponent::StaticClass()));
	}

	return nullptr;
}

bool UAttributeComponent::IsActorAlive(AActor* Actor)
{
	UAttributeComponent* HealthComp = Cast<UAttributeComponent>(Actor->GetComponentByClass(UAttributeComponent::StaticClass()));
	if (HealthComp)
	{
		return HealthComp->IsAlive();
	}
	return false;
}

