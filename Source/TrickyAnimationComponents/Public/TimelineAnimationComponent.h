﻿// MIT License Copyright (c) 2022 Artyom "Tricky Fat Cat" Volkov

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TimelineAnimationComponent.generated.h"

class UCurveFloat;
class UTimelineComponent;

UENUM(BlueprintType)
enum class ETimelineAnimationState: uint8
{
	Begin,
	End,
	Transition UMETA(Hidden),
	Pause UMETA(Hidden)
};

DECLARE_LOG_CATEGORY_CLASS(LogTimelineAnimationComponent, Display, Display);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTimelineAnimationStartedSignature, ETimelineAnimationState, TargetState);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTimelineAnimationReversedSignature,
                                            ETimelineAnimationState,
                                            NewTargetState);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTimelineAnimationFinishedSignature, ETimelineAnimationState, NewState);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTimelineAnimationPausedSignature);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTimelineAnimationResumedSignature);

/**
 * An actor component which animates transforms of chosen scene components using timeline.
 */

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TRICKYANIMATIONCOMPONENTS_API UTimelineAnimationComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UTimelineAnimationComponent();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	UTimelineComponent* AnimationTimeline = nullptr;

public:
	/**
	 * The initial state of the component.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Animation)
	ETimelineAnimationState InitialState = ETimelineAnimationState::Begin;

	UPROPERTY(BlueprintAssignable, Category="TrickyAnimations|TimelineAnimation")
	FOnTimelineAnimationStartedSignature OnAnimationStarted;

	UPROPERTY(BlueprintAssignable, Category="TrickyAnimations|TimelineAnimation")
	FOnTimelineAnimationReversedSignature OnAnimationReversed;

	UPROPERTY(BlueprintAssignable, Category="TrickyAnimations|TimelineAnimation")
	FOnTimelineAnimationFinishedSignature OnAnimationFinished;

	UPROPERTY(BlueprintAssignable, Category="TrickyAnimations|TimelineAnimation")
	FOnTimelineAnimationPausedSignature OnAnimationPaused;

	UPROPERTY(BlueprintAssignable, Category="TrickyAnimations|TimelineAnimation")
	FOnTimelineAnimationResumedSignature OnAnimationResumed;

	UFUNCTION(BlueprintCallable, Category="TrickyAnimations|TimelineAnimation")
	void Start();

	UFUNCTION(BlueprintCallable, Category="TrickyAnimations|TimelineAnimation")
	void Reverse();

	UFUNCTION(BlueprintCallable, Category="TrickyAnimations|TimelineAnimation")
	void Pause();

	UFUNCTION(BlueprintCallable, Category="TrickyAnimations|TimelineAnimation")
	void Resume();

	UFUNCTION(BlueprintGetter, Category="TrickyAnimations|TimelineAnimation")
	float GetAnimationTime() const;

	UFUNCTION(BlueprintSetter, Category="TrickyAnimations|TimelineAnimation")
	void SetAnimationTime(const float Value);

	UFUNCTION(BlueprintGetter, Category="TrickyAnimations|TimelineAnimation")
	UCurveFloat* GetAnimationCurve() const;

	UFUNCTION(BlueprintSetter, Category="TrickyAnimations|TimelineAnimation")
	void SetAnimationCurve(UCurveFloat* Value);

	/**
	 * Fills the AnimatedComponents array.
	 *
	 * @warning This function checks if the given scene component isn't a nullptr. If true, it won't be added to the array.
	 */
	UFUNCTION(BlueprintCallable, Category="TrickyAnimations|TimelineAnimation")
	void SetAnimatedComponents(UPARAM(ref) TArray<USceneComponent*>& Components);

	UFUNCTION(BlueprintCallable, Category="TrickyAnimations|TimelineAnimation")
	bool CanPlayAnimation() const;

private:
	UPROPERTY(EditAnywhere,
		BlueprintGetter=GetAnimationTime,
		BlueprintSetter=SetAnimationTime,
		Category="Animation",
		meta=(AllowPrivateAccess="true", ClampMin="0"))
	float AnimationTime = 1.f;

	UPROPERTY(EditAnywhere,
		BlueprintGetter=GetAnimationCurve,
		BlueprintSetter=SetAnimationCurve,
		Category="Animation",
		meta=(AllowPrivateAccess="true"))
	UCurveFloat* AnimationCurve = nullptr;

	/**
	 * Contain transform offsets for each scene component in AnimatedComponents array.
	 *
	 * @warning The number of transforms must be equal to the number of animated components.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Animation", meta=(AllowPrivateAccess="true"))
	TArray<FTransform> TransformOffsets;

	UPROPERTY()
	TArray<FTransform> InitialTransforms;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Animation|States", meta=(AllowPrivateAccess="true"))
	ETimelineAnimationState CurrentState = InitialState;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Animation|States", meta=(AllowPrivateAccess="true"))
	ETimelineAnimationState TargetState = ETimelineAnimationState::End;

	UPROPERTY(BlueprintReadOnly, Category="Animation", meta=(AllowPrivateAccess="true"))
	TArray<USceneComponent*> AnimatedComponents;

	UFUNCTION()
	void AnimateTransform(const float Progress);

	UFUNCTION()
	void FinishAnimation();

	void CalculatePlayRate() const;

	void LogWarning(const FString& Message) const;
};
