// MIT License Copyright (c) 2022 Artyom "Tricky Fat Cat" Volkov

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SplineAnimationComponent.generated.h"

class UTimelineComponent;
class UCurveFloat;
class USplineComponent;

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
	OneWay,
	Loop,
	PingPong,
	Manual
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TRICKYANIMATIONCOMPONENTS_API USplineAnimationComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	USplineAnimationComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
							   FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY()
	UTimelineComponent* AnimationTimeline = nullptr;

public:
	UFUNCTION(BlueprintCallable, Category="TrickyAnimations|SplineAnimation")
	void Start();

	UFUNCTION(BlueprintCallable, Category="TrickyAnimations|SplineAnimation")
	void Pause();

	UFUNCTION(BlueprintCallable, Category="TrickyAnimations|SplineAnimation")
	void Resume();

	UFUNCTION(BlueprintGetter, Category="TrickyAnimations|SplineAnimation")
	UCurveFloat* GetAnimationCurve() const;

	UFUNCTION(BlueprintSetter, Category="TrickyAnimations|SplineAnimation")
	void SetAnimationCurve(UCurveFloat* Value);

	UFUNCTION(BlueprintGetter, Category="TrickyAnimations|SplineAnimation")
	float GetAnimationTime() const;

	UFUNCTION(BlueprintSetter, Category="TrickyAnimations|SplineAnimation")
	void SetAnimationTime(const float Value);

	UFUNCTION(BlueprintGetter, Category="TrickyAnimations|SplineAnimation")
	bool GetUseConstantSpeed() const;

	UFUNCTION(BlueprintSetter, Category="TrickyAnimations|SplineAnimation")
	void SetUseConstantSpeed(const bool Value);

	UFUNCTION(BlueprintSetter, Category="TrickyAnimations|SplineAnimation")
	float GetConstantSpeed() const;

	UFUNCTION(BlueprintSetter, Category="TrickyAnimations|SplineAnimation")
	void SetConstantSpeed(const float Value);

protected:
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Animation", meta=(AllowPrivateAccess))
	ESplineAnimationMode AnimationMode = ESplineAnimationMode::OneWay;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Animation", meta=(AllowPrivateAccess))
	AActor* SplineActor = nullptr;

	UPROPERTY()
	USplineComponent* SplineComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintGetter=GetAnimationCurve, BlueprintSetter=SetAnimationCurve, Category="Animation",
		meta=(AllowPrivateAccess="true"))
	UCurveFloat* AnimationCurve = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Animation", meta=(AllowPrivateAccess, ClampMin = "0"))
	int32 StartPointIndex = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Animation", meta=(AllowPrivateAccess))
	bool bIsReversed = false;

	UPROPERTY(EditAnywhere, BlueprintGetter=GetAnimationTime, BlueprintSetter=SetAnimationTime, Category="Animation",
		meta=(AllowPrivateAccess, EditCondition="!bUseConstantSpeed", ClampMin="0"))
	float AnimationTime = 1.f;

	UPROPERTY(EditAnywhere, BlueprintGetter=GetUseConstantSpeed, BlueprintSetter=SetUseConstantSpeed,
		Category="Animation", meta=(AllowPrivateAccess, InlineEditConditionToggle))
	bool bUseConstantSpeed = false;

	UPROPERTY(EditAnywhere, BlueprintGetter=GetConstantSpeed, BlueprintSetter=SetConstantSpeed, Category="Animation",
		meta=(AllowPrivateAccess="true", EditCondition="bUseConstantSpeed", ClampMin="0"))
	float ConstantSpeed = 300.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Animation", meta=(AllowPrivateAccess="true"))
	FVector LocationOffset{FVector::ZeroVector};
	
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category="Animation|DebugInfo", meta=(AllowPrivateAccess="true"))
	ESplineAnimationState AnimationState = ESplineAnimationState::Idle;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category="Animation|DebugInfo", meta=(AllowPrivateAccess="true"))
	int32 CurrentPointIndex = 0;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category="Animation|DebugInfo", meta=(AllowPrivateAccess="true"))
	int32 NextPointIndex = 1;

	void CalculateNextPointIndex();

	UFUNCTION()
	void AnimateAlongSpline(const float Progress);

	UFUNCTION()
	void FinishAnimation();

	float GetSplineDistanceAtPoint(const int32 PointIndex) const;

	float GetPositionAtSpline(const int32 CurrentIndex, const int32 NextIndex, const float Progress) const;

	void CalculatePlayRate() const;

	void CalculateAnimationTime(const int32 CurrentIndex, const int32 TargetIndex);

	int32 GetLastPointIndex() const;
};
