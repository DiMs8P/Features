// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/AbilitySet.h"

TArray<FGameplayAbilitySpecHandle> UAbilitySet::GrantAbilitiesToAbilitySystem(UAbilitySystemComponent* AbilitySystemComponent) const
{
    check(AbilitySystemComponent)
    
    TArray<FGameplayAbilitySpecHandle> Handles;
    Handles.Reserve(AbilitySetItems.Num());

    for(const FAbilitySetItem AbilitySetItem : AbilitySetItems)
    {
        Handles.AddUnique(AbilitySystemComponent->GiveAbility(
            FGameplayAbilitySpec(
                AbilitySetItem.GameplayAbility,
                0,
                static_cast<uint32>(AbilitySetItem.InputKey)
                )
            ));
    }

    return Handles;
}
