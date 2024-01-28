#pragma once

UENUM(BlueprintType)
enum class EAbilityInput{
    None = 0 UMETA(Hidden),
    Jump = 1,
    PrimaryAttack = 2,
    SecondaryAttack = 3,
};