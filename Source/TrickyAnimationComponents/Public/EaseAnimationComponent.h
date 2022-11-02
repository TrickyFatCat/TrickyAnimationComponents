// MIT License Copyright (c) 2022 Artyom "Tricky Fat Cat" Volkov

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "EaseAnimationComponent.generated.h"

/**
 * A simple component which interpolates its owner towards the chosen actor in the level.
 */

UCLASS(ClassGroup=(TrickyAnimationComponents), meta=(BlueprintSpawnableComponent))
class TRICKYANIMATIONCOMPONENTS_API UEaseAnimationComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UEaseAnimationComponent();

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
		meta=(DisplayAfter="bIsEnabled", EditCondition="bFollowActor"))
	AActor* TargetActor = nullptr;

	/**
	 * The world location which will be used as a target location.
	 */
	UPROPERTY(EditAnywhere,
		BlueprintReadWrite,
		Category="Animation",
		meta=(DisplayAfter="bIsEnabled", EditCondition="!bFollowActor"))
	FVector SpecificLocation{FVector::ZeroVector};

	/**
	 * Location offset relative to the target location.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Animation", meta=(DisplayAfter="bIsEnabled"))
	FVector LocationOffset{FVector::ZeroVector};

	/**
	 * A type of the function which will be used for moving an owner.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Animation", meta=(DisplayAfter="bIsEnabled"))
	TEnumAsByte<EEasingFunc::Type> EasingFunction = EEasingFunc::EaseInOut;

	/**
	 * Determines the speed of interpolation.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Animation", meta=(DisplayAfter="bIsEnabled"))
	float Alpha = 0.15f;

	/**
	 * Blend exponent, used only with EaseIn, EaseOut, EaseInOut easing functions.
	 * 
	 * The higher the steeper the graph.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Animation", meta=(DisplayAfter="bIsEnabled"))
	float Exponent = 2.f;

	/**
	 * Amount of substeps, used only with the Step easing function.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Animation", meta=(DisplayAfter="bIsEnabled"))
	int32 SubStep = 10.f;

	UFUNCTION(BlueprintGetter, Category="TrickyAnimations|EaseAnimation")
	bool GetIsEnabled() const;

	UFUNCTION(BlueprintSetter, Category="TrickyAnimations|EaseAnimation")
	void SetIsEnabled(const bool Value);

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime,
	                           ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(EditAnywhere,
		BlueprintGetter=GetIsEnabled,
		BlueprintSetter=SetIsEnabled,
		Category="Animation",
		meta=(AllowPrivateAccess))
	bool bIsEnabled = true;

	FVector CurrentLocation{FVector::ZeroVector};

	FVector TargetLocation{FVector::ZeroVector};

	FVector NewLocation{FVector::ZeroVector};

	void EaseAxis(const float& CurrentLocationAxis, const float& TargetLocationAxis, float& NewLocationAxis) const;
};
