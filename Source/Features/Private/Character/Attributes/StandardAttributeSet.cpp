// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Attributes/StandardAttributeSet.h"

#include "GameplayEffectExtension.h"

void UStandardAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
    Super::PreAttributeChange(Attribute, NewValue);
    if (Attribute == GetHealthAttribute())
    {
        NewValue = FMath::Clamp(NewValue, 0.f, GetHealthMax());
    }
}

void UStandardAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
    Super::PostGameplayEffectExecute(Data);
    if (Data.EvaluatedData.Attribute == GetDamageAttribute())
    {
        const float LocalDamageDone = GetDamage();
        SetDamage(0.0f);

        if (LocalDamageDone > 0.0f)
        {
            const float NewHealth = GetHealth() - LocalDamageDone;
            SetHealth(FMath::Clamp(NewHealth, 0.f, GetHealthMax()));
        }
    }
}

void UStandardAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UStandardAttributeSet, Health, OldHealth);
}

void UStandardAttributeSet::OnRep_HealthMax(const FGameplayAttributeData& OldHealthMax)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UStandardAttributeSet, HealthMax, OldHealthMax);
}

void UStandardAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}
