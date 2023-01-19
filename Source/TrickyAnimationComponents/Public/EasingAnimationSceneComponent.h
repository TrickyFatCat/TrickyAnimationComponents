// MIT License Copyright. Created by Artyom "Tricky Fat Cat" Volkov

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "TrickyAnimationComponentsLibrary.h"
#include "EasingAnimationSceneComponent.generated.h"

/**
 * A simple component which interpolates its owner towards the chosen actor/location in the level.
 */
UCLASS(ClassGroup=(TrickyAnimationComponents), meta=(BlueprintSpawnableComponent))
class TRICKYANIMATIONCOMPONENTS_API UEasingAnimationSceneComponent : public USceneComponent
{
	GENERATED_BODY()

public:
	UEasingAnimationSceneComponent();

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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Animation")
	bool bIsLooping = false;
	/**
	 * Determines behavior of the animation.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Animation", meta=(EditCondition="bIsLooping", EditConditionHides))
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

	UFUNCTION(BlueprintGetter, Category="TrickyAnimations|EasingAnimationScene")
	bool GetIsPlaying() const;

	UFUNCTION(BlueprintCallable, Category="TrickyAnimations|EasingAnimationScene")
	void Start();

	UFUNCTION(BlueprintCallable, Category="TrickyAnimations|EasingAnimationScene")
	void Stop();

	UFUNCTION(BlueprintGetter, Category="TrickyAnimations|EasingAnimationScene")
	float GetEaseDuration() const;

	UFUNCTION(BlueprintSetter, Category="TrickyAnimations|EasingAnimationScene")
	void SetEaseDuration(const float Value);

	UFUNCTION(BlueprintGetter)
	FVector GetTargetLocation() const;

	UFUNCTION(BlueprintSetter)
	void SetTargetLocation(const FVector& Value);
	
	UFUNCTION(BlueprintGetter)
	FRotator GetTargetRotation() const;

	UFUNCTION(BlueprintSetter)
	void SetTargetRotation(const FRotator& Value);

	UFUNCTION(BlueprintGetter)
	FVector GetTargetScale() const;

	UFUNCTION(BlueprintSetter)
	void SetTargetScale(const FVector& Value);
private:
	float LaunchTime = 0.f;

	UPROPERTY(BlueprintGetter=GetIsPlaying,
		Category="Animation")
	bool bIsPlaying = false;

	/**
	 * For normal mode it's target value, for others it's delta value.
	 */
	UPROPERTY(EditAnywhere, BlueprintGetter=GetTargetLocation, BlueprintSetter=SetTargetLocation, Category="Animation",
		meta=(AllowPrivateAccess, EditCondition="bAnimateLocation"))
	FVector TargetLocation{FVector::ZeroVector};

	/**
	 * For normal mode it's target value, for others it's delta value.
	 */
	UPROPERTY(EditAnywhere, BlueprintGetter=GetTargetRotation, BlueprintSetter=SetTargetRotation, BlueprintReadWrite,
		Category="Animation",
		meta=(AllowPrivateAccess, EditCondition="bAnimateRotation"))
	FRotator TargetRotation{FRotator::ZeroRotator};

	/**
	 * For normal mode it's target value, for others it's delta value.
	 */
	UPROPERTY(EditAnywhere, BlueprintGetter=GetTargetScale, BlueprintSetter=SetTargetScale, Category="Animation",
		meta=(AllowPrivateAccess, EditCondition="bAnimateScale"))
	FVector TargetScale{FVector::OneVector};

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

	float EaseFloat(const float InitialValue, const float TargetValue);

	template<typename T>
	void SwapValues(T& A, T& B)
	{
		const T C = A;
		A = B;
		B = C;
	}
};