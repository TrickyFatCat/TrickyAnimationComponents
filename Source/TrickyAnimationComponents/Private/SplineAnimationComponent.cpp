// MIT License Copyright (c) 2022 Artyom "Tricky Fat Cat" Volkov


#include "SplineAnimationComponent.h"

#include "Components/SplineComponent.h"
#include "Components/TimelineComponent.h"

USplineAnimationComponent::USplineAnimationComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	AnimationTimeline = CreateDefaultSubobject<UTimelineComponent>("SplineTimeline");
}


void USplineAnimationComponent::BeginPlay()
{
	Super::BeginPlay();

	if (!SplineActor)
	{
		//Print error
	}
	else
	{
		SplineComponent = SplineActor->FindComponentByClass<USplineComponent>();

		if (!SplineComponent)
		{
			// Print error
		}
	}

	if (AnimationCurve)
	{
		FOnTimelineFloat AnimationProgress;
		AnimationProgress.BindUFunction(this, FName("AnimateAlongSpline"));
		AnimationTimeline->AddInterpFloat(AnimationCurve, AnimationProgress);

		FOnTimelineEvent AnimationFinished;
		AnimationFinished.BindUFunction(this, FName("FinishAnimation"));
		AnimationTimeline->SetTimelineFinishedFunc(AnimationFinished);

		if (bUseConstantSpeed)
		{
			CalculateAnimationTime(0, 1);
		}

		CalculatePlayRate();
	}
}


void USplineAnimationComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                              FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void USplineAnimationComponent::Start()
{
	AnimationTimeline->PlayFromStart();
	// Start logic
	// Call delegate
}

void USplineAnimationComponent::Pause()
{
	// Pause logic
	// Call delegate
}

void USplineAnimationComponent::Resume()
{
	// Resume logic
	// Call delegate
}

UCurveFloat* USplineAnimationComponent::GetAnimationCurve() const
{
	return AnimationCurve;
}

void USplineAnimationComponent::SetAnimationCurve(UCurveFloat* Value)
{
	AnimationCurve = Value;
}

float USplineAnimationComponent::GetAnimationTime() const
{
	return AnimationTime;
}

void USplineAnimationComponent::SetAnimationTime(const float Value)
{
	if (bUseConstantSpeed)
	{
		return;
	}

	if (Value <= 0.f)
	{
		// Print error
		return;
	}

	AnimationTime = Value;
	CalculatePlayRate();
}

bool USplineAnimationComponent::GetUseConstantSpeed() const
{
	return bUseConstantSpeed;
}

void USplineAnimationComponent::SetUseConstantSpeed(const bool Value)
{
	bUseConstantSpeed = Value;
	CalculateAnimationTime(0, 1); // Change to points array;
	CalculatePlayRate();
	// Recalculate speed;
}

float USplineAnimationComponent::GetConstantSpeed() const
{
	return ConstantSpeed;
}

void USplineAnimationComponent::SetConstantSpeed(const float Value)
{
	if (!bUseConstantSpeed)
	{
		return;
	}

	if (Value <= 0.f)
	{
		// Print error
		return;
	}

	ConstantSpeed = Value;
	CalculateAnimationTime(0, 1); // Rework
	CalculatePlayRate();
}

void USplineAnimationComponent::AnimateAlongSpline(const float Progress)
{
	if (!SplineComponent)
	{
		return;
	}

	const FVector NewLocation{
		SplineComponent->GetLocationAtDistanceAlongSpline(GetPositionAtSpline(0, 1, Progress),
		                                                  ESplineCoordinateSpace::World)
	};

	GetOwner()->SetActorLocation(NewLocation);
}

void USplineAnimationComponent::FinishAnimation()
{
	// Add logic
	// Call delegate
}

float USplineAnimationComponent::GetSplineDistanceAtPoint(const int32 PointIndex)
{
	if (!SplineComponent) return -1.f;

	return SplineComponent->GetDistanceAlongSplineAtSplinePoint(PointIndex);
	// Rework in the future using array of points
}

float USplineAnimationComponent::GetPositionAtSpline(const int32 CurrentPointIndex, const int32 NextPointIndex,
                                                     const float Progress)
{
	if (!SplineComponent) return -1;

	const float Start = GetSplineDistanceAtPoint(CurrentPointIndex);
	const float Finish = GetSplineDistanceAtPoint(NextPointIndex);

	return FMath::Lerp(Start, Finish, Progress);
}

void USplineAnimationComponent::CalculatePlayRate() const
{
	if (!AnimationCurve)
	{
		return;
	}

	float MinTime = 0.f;
	float MaxTime = 0.f;

	AnimationCurve->GetTimeRange(MinTime, MaxTime);

	if (MaxTime <= 0.f)
	{
		// Print error
		MaxTime = 1.f;
	}

	AnimationTimeline->SetPlayRate(MaxTime / AnimationTime);
}

void USplineAnimationComponent::CalculateAnimationTime(const int32 CurrentPointIndex, const int32 NextPointIndex)
{
	if (!SplineComponent)
	{
		// Print error
		return;
	}

	if (bUseConstantSpeed)
	{
		const float StartDistance = GetSplineDistanceAtPoint(CurrentPointIndex);
		const float FinishDistance = GetSplineDistanceAtPoint(NextPointIndex);
		const float DistanceBetweenPoints = FMath::Abs(FinishDistance - StartDistance);
		AnimationTime = DistanceBetweenPoints / ConstantSpeed;
	}
}
