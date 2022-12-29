// MIT License Copyright (c) 2022 Artyom "Tricky Fat Cat" Volkov

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "EaseAnimationComponent.generated.h"

/**
 * A simple component which interpolates its owner towards the chosen actor/location in the level.
 */

UCLASS(ClassGroup=(TrickyAnimationComponents), meta=(BlueprintSpawnableComponent))
class TRICKYANIMATIONCOMPONENTS_API UEaseAnimationComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UEaseAnimationComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime,
	                           ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	/**
	 * Toggles if the component will interpolate position towards a target actor or a specific location.
	 */
	UPROPERTY(EditAnywhere,
		BlueprintReadWrite,
		Category="Animation",
		meta=(DisplayAfter="bIsEnabled", InlineEditConditionToggle))
	bool bFollowActor = true;

	/**
	 * An actor which world location will be used as a target location.
	 */
	UPROPERTY(EditAnywhere,
		BlueprintReadWrite,
		Category="Animation",
		meta=(DisplayAfter="bIsEnabled", EditCondition="bFollowActor", EditConditionHides))
	AActor* TargetActor = nullptr;

	/**
	 * The world location which will be used as a target location.
	 */
	UPROPERTY(EditAnywhere,
		BlueprintReadWrite,
		Category="Animation",
		meta=(DisplayAfter="bIsEnabled", EditCondition="!bFollowActor", EditConditionHides))
	FVector Location{FVector::ZeroVector};

	/**
	 * Location offset relative to the target location.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Animation", meta=(DisplayAfter="EaseDuration"))
	FVector TargetLocationOffset{FVector::ZeroVector};

	/**
	 * A type of the function which will be used for moving an owner.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Animation", meta=(DisplayAfter="EaseDuration"))
	TEnumAsByte<EEasingFunc::Type> EaseFunction = EEasingFunc::EaseInOut;

	/**
	 * Blend exponent, used only with EaseIn, EaseOut, EaseInOut easing functions.
	 * 
	 * The higher the steeper the graph.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Animation", meta=(DisplayAfter="EaseDuration"))
	float Exponent = 2.f;

	/**
	 * Amount of substeps, used only with the Step easing function.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Animation", meta=(DisplayAfter="EaseDuration"))
	int32 SubStep = 10.f;

	UFUNCTION(BlueprintGetter, Category="TrickyAnimations|EaseAnimation")
	bool GetIsEnabled() const;

	UFUNCTION(BlueprintSetter, Category="TrickyAnimations|EaseAnimation")
	void SetIsEnabled(const bool Value);

	UFUNCTION(BlueprintGetter, Category="TrickyAnimations|EaseAnimation")
	float GetEaseDuration() const;

	UFUNCTION(BlueprintSetter, Category="TrickyAnimations|EaseAnimation")
	void SetEaseDuration(const float Value);

private:
	float LaunchTime = 0.f;

	UPROPERTY(EditAnywhere,
		BlueprintGetter=GetIsEnabled,
		BlueprintSetter=SetIsEnabled,
		Category="Animation",
		meta=(AllowPrivateAccess))
	bool bIsEnabled = true;

	/**
	 * Determines the duration of easing.
	 */
	UPROPERTY(EditAnywhere,
		BlueprintGetter=GetEaseDuration,
		BlueprintSetter=SetEaseDuration,
		Category="Animation",
		meta=(DisplayAfter="bIsEnabled"))
	float EaseDuration = 1.f;

	FVector InitialLocation{FVector::ZeroVector};

	FVector TargetLocation{FVector::ZeroVector};

	FVector NewLocation{FVector::ZeroVector};

	float EaseAxis(const float InitialValue, const float TargetValue);
};
