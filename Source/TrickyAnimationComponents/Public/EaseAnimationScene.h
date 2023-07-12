// MIT License Copyright (c) Artyom "Tricky Fat Cat" Volkov

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Libraries/TrickyAnimationComponentsLibrary.h"
#include "Libraries/TrickyEasingLibrary.h"
#include "EaseAnimationScene.generated.h"

/**
 * A scene component which can animate its location, rotation and scale using easing functions.
 */
UCLASS(ClassGroup=(TrickyAnimationComponents), meta=(BlueprintSpawnableComponent))
class TRICKYANIMATIONCOMPONENTS_API UEaseAnimationScene : public USceneComponent
{
	GENERATED_BODY()

public:
	UEaseAnimationScene();

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

	/**Ease function which will be used for animation.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Animation")
	EEaseFunction EaseFunction = EEaseFunction::Linear;

	UFUNCTION(BlueprintGetter, Category="TrickyAnimations|EasingAnimationScene")
	bool GetIsPlaying() const;

	/**Starts the animation from initial location/rotation/scale.*/
	UFUNCTION(BlueprintCallable, Category="TrickyAnimations|EasingAnimationScene")
	bool PlayFromStart();

	/**Starts the animation from target location/rotation/scale.*/
	UFUNCTION(BlueprintCallable, Category="TrickyAnimations|EasingAnimationScene")
	bool PlayFromEnd();

	/**Stops the animation.*/
	UFUNCTION(BlueprintCallable, Category="TrickyAnimations|EasingAnimationScene")
	bool Stop();

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

	/**Target relative location of the animation.*/
	UPROPERTY(EditAnywhere, BlueprintGetter=GetTargetLocation, BlueprintSetter=SetTargetLocation, Category="Animation",
		meta=(AllowPrivateAccess, EditCondition="bAnimateLocation"))
	FVector TargetLocation{FVector::ZeroVector};

	/**Target relative rotation of the animation.*/
	UPROPERTY(EditAnywhere, BlueprintGetter=GetTargetRotation, BlueprintSetter=SetTargetRotation, BlueprintReadWrite,
		Category="Animation",
		meta=(AllowPrivateAccess, EditCondition="bAnimateRotation"))
	FRotator TargetRotation{FRotator::ZeroRotator};

	/**Target relative scale of the animation.*/
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
};
