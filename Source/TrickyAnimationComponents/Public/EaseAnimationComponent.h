// MIT License Copyright (c) Artyom "Tricky Fat Cat" Volkov

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "TrickyAnimationComponentsLibrary.h"
#include "EaseAnimationComponent.generated.h"

/**
 * An actor component which can animate owners location, rotation and scale using easing functions.
 */
UCLASS(ClassGroup=(TrickyAnimationComponents), meta=(BlueprintSpawnableComponent))
class TRICKYANIMATIONCOMPONENTS_API UEaseAnimationComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UEaseAnimationComponent();

protected:
	virtual void InitializeComponent() override;
	
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime,
	                           ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	/**Called when the animation cycle is finished.*/
	UPROPERTY(BlueprintAssignable)
	FOnAnimationFinishedSignature OnAnimationFinished;

	/**Toggles if the animation will start on begin play.*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Animation")
	bool bAutoPlay = false;
	
	/**If true, PlayFormEnd function will be called on begin play, else PlayFromStart.*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Animation", meta=(EditCondition="bAutoPlay", EditConditionHides))
	bool bPlayFromEnd = false;
	
	/**Determines behavior of the animation.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Animation")
	EEaseAnimBehavior AnimationBehavior = EEaseAnimBehavior::Normal;

	/**If true, relative location will be animated.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Animation", meta=(InlineEditConditionToggle))
	bool bAnimateLocation = true;

	/**If true, relative rotation will be animated.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Animation", meta=(InlineEditConditionToggle))
	bool bAnimateRotation = false;

	/**If true, relative scale will be animated.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Animation", meta=(InlineEditConditionToggle, AllowPreserveRatio="true"))
	bool bAnimateScale = false;

	/**Ease function which will be used for the animation.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Animation")
	TEnumAsByte<EEasingFunc::Type> EaseFunction = EEasingFunc::EaseInOut;

	

	/**The higher the steeper the graph.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Animation",
		meta=(EditCondition=
			"EaseFunction == EEasingFunc::EaseIn || EaseFunction == EEasingFunc::EaseOut || EaseFunction == EEasingFunc::EaseInOut"
			,
			EditConditionHides
		))
	float BlendExp = 2.f;

	/**Amount of substeps.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Animation",
		meta=(EditCondition="EaseFunction == EEasingFunc::Step", EditConditionHides))
	int32 Steps = 10.f;

	UFUNCTION(BlueprintGetter, Category="TrickyAnimations|EaseAnimation")
	bool GetIsPlaying() const;

	/**Starts the animation from initial location/rotation/scale.*/
	UFUNCTION(BlueprintCallable, Category="TrickyAnimations|EaseAnimation")
	bool PlayFromStart();

	/**Starts the animation from target location/rotation/scale.*/
	UFUNCTION(BlueprintCallable, Category="TrickyAnimations|EaseAnimation")
	bool PlayFromEnd();
	
	/**Stops the animation.*/
	UFUNCTION(BlueprintCallable, Category="TrickyAnimations|EaseAnimation")
	bool Stop();

	UFUNCTION(BlueprintGetter, Category="TrickyAnimations|EaseAnimation")
	float GetEaseDuration() const;

	UFUNCTION(BlueprintSetter, Category="TrickyAnimations|EaseAnimation")
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

	/**Target world location of the animation.*/
	UPROPERTY(EditAnywhere, BlueprintGetter=GetTargetLocation, BlueprintSetter=SetTargetLocation, Category="Animation",
		meta=(AllowPrivateAccess, EditCondition="bAnimateLocation"))
	FVector TargetLocation{FVector::ZeroVector};

	/**Target world rotation of the animation.*/
	UPROPERTY(EditAnywhere, BlueprintGetter=GetTargetRotation, BlueprintSetter=SetTargetRotation, BlueprintReadWrite,
		Category="Animation",
		meta=(AllowPrivateAccess, EditCondition="bAnimateRotation"))
	FRotator TargetRotation{FRotator::ZeroRotator};

	/**Target world scale of the animation.*/
	UPROPERTY(EditAnywhere, BlueprintGetter=GetTargetScale, BlueprintSetter=SetTargetScale, Category="Animation",
		meta=(AllowPrivateAccess, EditCondition="bAnimateScale"))
	FVector TargetScale{FVector::OneVector};

	/**Animation duration.*/
	UPROPERTY(EditAnywhere,
		BlueprintGetter=GetEaseDuration,
		BlueprintSetter=SetEaseDuration,
		Category="Animation", meta=(DisplayAfter="AnimationBehavior"))
	float Duration = 1.f;

	FVector InitialLocation{FVector::ZeroVector};
	FRotator InitialRotation{FRotator::ZeroRotator};
	FVector InitialScale{FVector::ZeroVector};

	FVector StartLocation{FVector::ZeroVector};
	FRotator StartRotation{FRotator::ZeroRotator};
	FVector StartScale{FVector::OneVector};

	FVector EndLocation{FVector::ZeroVector};
	FRotator EndRotation{FRotator::ZeroRotator};
	FVector EndScale{FVector::OneVector};
	
	void Finish();

	void EaseVector(FVector& Value, const FVector& InitialValue, const FVector& TargetValue, const float Alpha) const;

	void EaseRotator(FRotator& Value, const FRotator& InitialValue, const FRotator& TargetValue, const float Alpha) const;
};
