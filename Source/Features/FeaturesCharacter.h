// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "AbilitySystemInterface.h"
#include "GameplayAbilitySpecHandle.h"
#include "GameplayEffectTypes.h"
#include "Abilities/AbilityInput.h"
#include "FeaturesCharacter.generated.h"

class UGameplayEffect;
class UStandardAttributeSet;
class UAbilitySystemComponent;
class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
class UAbilitySet;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

USTRUCT()
struct FAbilityInputToInputActionBinding
{
    GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly, Category=Input)
    UInputAction* InputAction;

    UPROPERTY(EditDefaultsOnly, Category=Input)
    EAbilityInput AbilityInput;
};

USTRUCT()
struct FAbilityInputBindings
{
    GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly, Category=Input)
    TArray<FAbilityInputToInputActionBinding> Bindings;
};

UCLASS(config=Game)
class AFeaturesCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

    UPROPERTY(VisibleAnywhere, Category=Abilities)
    UAbilitySystemComponent* AbilitySystemComponent;

    UPROPERTY(EditDefaultsOnly, Category=Abilities)
    UStandardAttributeSet* StandardAttributeSet;

    UPROPERTY(EditDefaultsOnly, Category=Abilities)
    UAbilitySet* InitialAbilitySet;

    UPROPERTY(EditDefaultsOnly, Category=Abilities)
    TSubclassOf<UGameplayEffect> InitialGameplayEffect;

    UPROPERTY(EditDefaultsOnly, Category="Input|Bindings")
    FAbilityInputBindings AbilityInputBindings;

private:
    UPROPERTY(Transient)
    TArray<FGameplayAbilitySpecHandle> InitiallyGrantedAbilitySpecHandles;

public:
	AFeaturesCharacter();
	

protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);
			

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// To add mapping context
	virtual void BeginPlay();

    // Begin IAbilitySystemInterface
    virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override {return AbilitySystemComponent;}
    // End IAbilitySystemInterface

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

private:
    void SetupInitialAbilitiesAndEffects();

    void AbilityInputBindingPressedHandler(EAbilityInput AbilityInput);
    void AbilityInputBindingReleasedHandler(EAbilityInput AbilityInput);

    void OnHealthAttributeChanged(const FOnAttributeChangeData& OnAttributeChangeData);
};

