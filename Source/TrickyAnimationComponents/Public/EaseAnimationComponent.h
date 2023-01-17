// MIT License Copyright. Created by Artyom "Tricky Fat Cat" Volkov

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "TrickyAnimationComponentsLibrary.h"
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

	UPROPERTY(BlueprintAssignable)
	FOnAnimationStartedSignature OnAnimationStarted;

	UPROPERTY(BlueprintAssignable)
	FOnAnimationStoppedSignature OnAnimationStopped;

	UPROPERTY(BlueprintAssignable)
	FOnAnimationFinishedSignature OnAnimationFinished;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Animation")
	bool bStartOnBeginPlay = false;

	/**
	 * Determines behavior of the animation.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Animation")
	EEaseAnimBehavior AnimationBehavior = EEaseAnimBehavior::Normal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(InlineEditConditionToggle))
	bool bAnimateLocation = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(InlineEditConditionToggle))
	bool bAnimateRotation = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(InlineEditConditionToggle, AllowPreserveRatio="true"))
	bool bAnimateScale = false;


	/**
	 * A type of the function which will be used for moving an owner.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Animation")
	TEnumAsByte<EEasingFunc::Type> EaseFunction = EEasingFunc::EaseInOut;

	/**
	 * Blend exponent, used only with EaseIn, EaseOut, EaseInOut easing functions.
	 * 
	 * The higher the steeper the graph.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Animation",
		meta=(EditCondition=
			"EaseFunction == EEasingFunc::EaseIn || EaseFunction == EEasingFunc::EaseOut || EaseFunction == EEasingFunc::EaseInOut"
			,
			EditConditionHides
		))
	float Exponent = 2.f;

	/**
	 * Amount of substeps, used only with the Step easing function.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Animation",
		meta=(EditCondition="EaseFunction == EEasingFunc::Step", EditConditionHides))
	int32 SubStep = 10.f;

	UFUNCTION(BlueprintGetter, Category="TrickyAnimations|EaseAnimation")
	bool GetIsPlaying() const;

	UFUNCTION(BlueprintCallable, Category="TrickyAnimations|EaseAnimation")
	void StartAnimation();

	UFUNCTION(BlueprintCallable, Category="TrickyAnimations|EaseAnimation")
	void StopAnimation();

	UFUNCTION(BlueprintGetter, Category="TrickyAnimations|EaseAnimation")
	float GetEaseDuration() const;

	UFUNCTION(BlueprintSetter, Category="TrickyAnimations|EaseAnimation")
	void SetEaseDuration(const float Value);

	UFUNCTION(BlueprintGetter)
	FVector GetLocation() const;

	UFUNCTION(BlueprintSetter)
	void SetLocation(const FVector& Value);
	
	UFUNCTION(BlueprintGetter)
	FRotator GetRotation() const;

	UFUNCTION(BlueprintSetter)
	void SetRotation(const FRotator& Value);

	UFUNCTION(BlueprintGetter)
	FVector GetScale() const;

	UFUNCTION(BlueprintSetter)
	void SetScale(const FVector& Value);
private:
	float LaunchTime = 0.f;

	UPROPERTY(BlueprintGetter=GetIsPlaying,
		Category="Animation")
	bool bIsPlaying = false;

	/**
	 * For normal mode it's target value, for others it's delta value.
	 */
	UPROPERTY(EditAnywhere, BlueprintGetter=GetLocation, BlueprintSetter=SetLocation, Category="Animation",
		meta=(AllowPrivateAccess, EditCondition="bAnimateLocation"))
	FVector Location{FVector::ZeroVector};

	/**
	 * For normal mode it's target value, for others it's delta value.
	 */
	UPROPERTY(EditAnywhere, BlueprintGetter=GetRotation, BlueprintSetter=SetRotation, BlueprintReadWrite,
		Category="Animation",
		meta=(AllowPrivateAccess, EditCondition="bAnimateRotation"))
	FRotator Rotation{FRotator::ZeroRotator};

	/**
	 * For normal mode it's target value, for others it's delta value.
	 */
	UPROPERTY(EditAnywhere, BlueprintGetter=GetScale, BlueprintSetter=SetScale, Category="Animation",
		meta=(AllowPrivateAccess, EditCondition="bAnimateScale"))
	FVector Scale{FVector::OneVector};

	/**
	 * Determines the duration of easing.
	 */
	UPROPERTY(EditAnywhere,
		BlueprintGetter=GetEaseDuration,
		BlueprintSetter=SetEaseDuration,
		Category="Animation", meta=(DisplayAfter="AnimationBehavior"))
	float Duration = 1.f;

	FVector InitialLocation{FVector::ZeroVector};
	FRotator InitialRotation{FRotator::ZeroRotator};
	FVector InitialScale{FVector::ZeroVector};

	FVector TargetLocation{FVector::ZeroVector};
	FRotator TargetRotation{FRotator::ZeroRotator};
	FVector TargetScale{FVector::ZeroVector};

	int32 PinPongDirection = 1;

	float EaseFloat(const float InitialValue, const float TargetValue);

	void GetInitialValues();

	void CalculateTargetValues();
};
