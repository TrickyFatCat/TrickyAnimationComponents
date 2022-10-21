// MIT License Copyright (c) 2022 Artyom "Tricky Fat Cat" Volkov

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SplineAnimationComponent.generated.h"

class UTimelineComponent;
class UCurveFloat;
class USplineComponent;

DECLARE_LOG_CATEGORY_CLASS(LogSplineAnimationComponent, Display, Display);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSplineAnimationStartedSignature);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSplineAnimationStoppedSignature, int32, PointIndex);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSplineAnimationPausedSignature);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSplineAnimationResumedSignature);

UENUM()
enum class ESplineAnimationState : uint8
{
	Idle,
	Transition,
	Wait,
	Pause
};

UENUM()
enum class ESplineAnimationMode : uint8
{
	OneWay UMETA(ToolTip="Animate from the first to the last spline point."),
	Loop UMETA(ToolTip="Loop the animation from first to the last spline point."),
	PingPong UMETA(ToolTip="Move forth and beck between the first and the last spline point."),
	Manual UMETA(ToolTip="Create the custom movement pattern using the AnimateTo function.")
};

USTRUCT(BlueprintType)
struct FAxisInheritance
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category="Inheritance")
	bool bX = false;

	UPROPERTY(EditAnywhere, Category="Inheritance")
	bool bY = false;

	UPROPERTY(EditAnywhere, Category="Inheritance")
	bool bZ = false;
};

/**
 * A simple actor component which can animate the owner along the spline component.
 */

UCLASS(ClassGroup=(TrcickyAnimationComponent), meta=(BlueprintSpawnableComponent))
class TRICKYANIMATIONCOMPONENTS_API USplineAnimationComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	USplineAnimationComponent();

	virtual void Activate(bool bReset) override;

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime,
	                           ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintAssignable, Category="Animation")
	FOnSplineAnimationStartedSignature OnAnimationStarted;

	UPROPERTY(BlueprintAssignable, Category="Animation")
	FOnSplineAnimationStoppedSignature OnAnimationStopped;

	UPROPERTY(BlueprintAssignable, Category="Animation")
	FOnSplineAnimationPausedSignature OnAnimationPaused;

	UPROPERTY(BlueprintAssignable, Category="Animation")
	FOnSplineAnimationResumedSignature OnAnimationResumed;

private:
	UPROPERTY()
	UTimelineComponent* AnimationTimeline = nullptr;

public:
	UFUNCTION(BlueprintCallable, Category="TrickyAnimations|SplineAnimation")
	void Start();

	UFUNCTION(BlueprintCallable, Category="TrickyAnimations|SplineAnimation")
	void Stop();

	UFUNCTION(BlueprintCallable, Category="TrickyAnimations|SplineAnimation")
	void AnimateTo(const int32 PointIndex);

	UFUNCTION(BlueprintCallable, Category="TrickyAnimations|SplineAnimation")
	void Pause();

	UFUNCTION(BlueprintCallable, Category="TrickyAnimations|SplineAnimation")
	void Resume();

	UFUNCTION(BlueprintGetter, Category="TrickyAnimations|SplineAnimation")
	AActor* GetSplineActor() const;

	UFUNCTION(BlueprintSetter, Category="TrickyAnimations|SplineAnimation")
	void SetSplineActor(AActor* Value);

	UFUNCTION(BlueprintGetter, Category="TrickyAnimations|SplineAnimation")
	UCurveFloat* GetAnimationCurve() const;

	UFUNCTION(BlueprintSetter, Category="TrickyAnimations|SplineAnimation")
	void SetAnimationCurve(UCurveFloat* Value);

	UFUNCTION(BlueprintGetter, Category="TrickyAnimations|SplineAnimation")
	bool GetIsReversed() const;

	UFUNCTION(BlueprintSetter, Category="TrickyAnimations|SplineAnimation")
	void SetIsReversed(const bool Value);

	UFUNCTION(BlueprintGetter, Category="TrickyAnimations|SplineAnimation")
	float GetAnimationTime() const;

	UFUNCTION(BlueprintSetter, Category="TrickyAnimations|SplineAnimation")
	void SetAnimationTime(const float Value);

	UFUNCTION(BlueprintGetter, Category="TrickyAnimations|SplineAnimation")
	bool GetUseAnimationSpeed() const;

	UFUNCTION(BlueprintSetter, Category="TrickyAnimations|SplineAnimation")
	void SetUseAnimationSpeed(const bool Value);

	UFUNCTION(BlueprintSetter, Category="TrickyAnimations|SplineAnimation")
	float GetAnimationSpeed() const;

	UFUNCTION(BlueprintSetter, Category="TrickyAnimations|SplineAnimation")
	void SetAnimationSpeed(const float Value);

protected:
private:
	/**
	 * Determines the behavior of the animation.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Animation", meta=(AllowPrivateAccess))
	ESplineAnimationMode AnimationMode = ESplineAnimationMode::OneWay;

	/**
	 * An actor which has a spline component.
	 *
	 * @warning Use a separate actor with a spline component.
	 */
	UPROPERTY(EditInstanceOnly,
		BlueprintGetter=GetSplineActor,
		BlueprintSetter=SetSplineActor,
		Category="Animation",
		meta=(AllowPrivateAccess))
	AActor* SplineActor = nullptr;

	UPROPERTY(BlueprintReadOnly, Category="Animation", meta=(AllowPrivateAccess))
	USplineComponent* SplineComponent = nullptr;

	/**
	 * A float curve object used by the timeline component for the animation.
	 *
	 * It's better to use a curve with length equal 1.
	 */
	UPROPERTY(EditAnywhere,
		BlueprintGetter=GetAnimationCurve,
		BlueprintSetter=SetAnimationCurve,
		Category="Animation",
		meta=(AllowPrivateAccess="true"))
	UCurveFloat* AnimationCurve = nullptr;

	UPROPERTY(EditAnywhere,
		BlueprintGetter=GetUseAnimationSpeed,
		BlueprintSetter=SetUseAnimationSpeed,
		Category="Animation",
		meta=(AllowPrivateAccess, InlineEditConditionToggle))
	bool bUseAnimationSpeed = false;

	/**
	 * Length of the animation.
	 */
	UPROPERTY(EditAnywhere,
		BlueprintGetter=GetAnimationTime,
		BlueprintSetter=SetAnimationTime,
		Category="Animation",
		meta=(AllowPrivateAccess, EditCondition="!bUseAnimationSpeed", ClampMin="0"))
	float AnimationTime = 1.f;

	/**
	 * Using for calculating the animation time.
	 *
	 * Great for splines with many points and when the animation time between them must be constant.
	 */
	UPROPERTY(EditAnywhere,
		BlueprintGetter=GetAnimationSpeed,
		BlueprintSetter=SetAnimationSpeed,
		Category="Animation",
		meta=(AllowPrivateAccess="true", EditCondition="bUseAnimationSpeed", ClampMin="0"))
	float AnimationSpeed = 300.f;

	/**
	 * The point index from which the animation will be started.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Animation", meta=(AllowPrivateAccess, ClampMin = "0"))
	int32 StartPointIndex = 0;

	/**
	 * Determines if the order of points will be reversed or not.
	 */
	UPROPERTY(EditAnywhere,
		BlueprintGetter=GetIsReversed,
		BlueprintSetter=SetIsReversed,
		Category="Animation",
		meta=(AllowPrivateAccess))
	bool bIsReversed = false;

	/**
	 * Toggle if should an owner stopped at the spline points during the animation.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Animation|StopsOptions", meta=(AllowPrivateAccess))
	bool bStopAtPoints = false; // TODO Consider creating custom getter and setter

	/**
	 * If true, the actor will "stop" at start point at the beginning of the animation.
	 */ 
	UPROPERTY(EditAnywhere,
		BlueprintReadOnly,
		Category="Animation|StopsOptions",
		meta=(AllowPrivateAccess, EditCondition="bStopAtPoints"))
	bool bWaitAtStart = true;

	/**
	 * How long the owner will wait at the point.
	 */
	UPROPERTY(EditAnywhere,
		BlueprintReadWrite,
		Category="Animation|StopsOptions",
		meta=(AllowPrivateAccess, EditCondition="bStopAtPoints && !bUseCustomStops", ClampMin=0.f))
	float WaitTime = 1.f;

	UPROPERTY(EditInstanceOnly,
		BlueprintReadOnly,
		Category="Animation|StopsOptions",
		meta=(AllowPrivateAccess, EditCondition="bStopAtpoints"))
	bool bUseCustomStops = false;

	/**
	 * 
	 */
	UPROPERTY(EditInstanceOnly,
		BlueprintReadOnly,
		Category="Animation|StopsOptions",
		meta=(AllowPrivateAccess, EditCondition="bUseCustomStops && bStopAtPoints"))
	TMap<int32, float> CustomStops;

	UPROPERTY(BlueprintReadOnly, Category="Animation|StopsOptions", meta=(AllowPrivateAccess))
	FTimerHandle WaitTimerHandle;

	/**
	 * The offset along the spline.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Animation|TransformOptions", meta=(AllowPrivateAccess))
	float SplineOffset = 0.f;

	/**
	 * Location offset relative to the current location along the spline.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Animation|TransformOptions", meta=(AllowPrivateAccess))
	FVector LocationOffset{FVector::ZeroVector};

	/**
	 * Determines if the rotation along spline must be applied to the owner.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Animation|TransformOptions", meta=(AllowPrivateAccess))
	FAxisInheritance InheritRotation;

	/**
	 * Determines if the scale along spline must be applied to the owner.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Animation|TransformOptions", meta=(AllowPrivateAccess))
	FAxisInheritance InheritScale;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category="Animation|DebugInfo", meta=(AllowPrivateAccess))
	ESplineAnimationState AnimationState = ESplineAnimationState::Idle;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category="Animation|DebugInfo", meta=(AllowPrivateAccess))
	float CurrentAnimationTime = 0.f;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category="Animation|DebugInfo", meta=(AllowPrivateAccess))
	int32 CurrentPointIndex = 0;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category="Animation|DebugInfo", meta=(AllowPrivateAccess))
	int32 NextPointIndex = 1;
	
	UPROPERTY(VisibleInstanceOnly, Category="Animation|DebugInfo", meta=(AllowPrivateAccess))
	TArray<int32> PointsIndexes;
	
	bool bMustStop = false;

	void CalculateNextPointIndex();

	UFUNCTION()
	void AnimateAlongSpline(const float Progress) const;

	void MoveAlongSpline(const float Progress) const;

	void RotateAlongSpline(const float Progress) const;

	void ScaleAlongSpline(const float Progress) const;

	UFUNCTION()
	void FinishAnimation();

	float GetSplineDistanceAtPoint(const int32 PointIndex) const;

	float GetPositionAtSpline(const int32 CurrentIndex, const int32 NextIndex, const float Progress) const;

	void CalculatePlayRate() const;

	void CalculateAnimationTime(const int32 CurrentIndex, const int32 TargetIndex);

	int32 GetLastPointIndex() const;

	int32 GetLastSplinePoint() const;

	void StartWaitTimer();

	void Continue();

	void LogWarning(const FString& Message) const;

	bool HasSplineComponent() const;
};
