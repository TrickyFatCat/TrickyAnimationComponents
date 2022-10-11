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
		else
		{
			if (StartPointIndex > GetLastPointIndex())
			{
				StartPointIndex = 0;
				// Print error
			}
			CurrentPointIndex = StartPointIndex;
			CalculateNextPointIndex();
			CalculateAnimationTime(CurrentPointIndex, NextPointIndex); // TODO Rework for stopping on each point
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
	if (AnimationState != ESplineAnimationState::Idle)
	{
		// Print error
		return;
	}

	CalculateAnimationTime(CurrentPointIndex, NextPointIndex); // TODO rework for stopping on each point
	CalculatePlayRate();
	AnimationTimeline->PlayFromStart();
	AnimationState = ESplineAnimationState::Transition;
	// Start logic
	// Call delegate
}

void USplineAnimationComponent::Pause()
{
	if (AnimationState != ESplineAnimationState::Transition)
	{
		// Print error
		return;
	}

	AnimationTimeline->Stop();
	AnimationState = ESplineAnimationState::Pause;
	// Pause logic
	// Call delegate
}

void USplineAnimationComponent::Resume()
{
	if (AnimationState != ESplineAnimationState::Pause)
	{
		// Print error
		return;
	}

	AnimationTimeline->Play(); // Improve logic considering indexes
	AnimationState = ESplineAnimationState::Transition;
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

	if (bUseConstantSpeed)
	{
		CalculateAnimationTime(CurrentPointIndex, NextPointIndex); // TODO Rework for stopping on each point
		CalculatePlayRate();
	}
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
	CalculateAnimationTime(CurrentPointIndex, NextPointIndex); // TODO Rework for stopping on each point
	CalculatePlayRate();
}

void USplineAnimationComponent::CalculateNextPointIndex()
{
	switch (AnimationMode)
	{
	case ESplineAnimationMode::OneWay:
		NextPointIndex = bIsReversed ? 0 : GetLastPointIndex();
	// Implement logic
		break;

	case ESplineAnimationMode::Loop:
		NextPointIndex = bIsReversed ? 0 : GetLastPointIndex();
	//Implement logic
		break;

	case ESplineAnimationMode::PingPong:
		if (bIsReversed)
		{
			NextPointIndex = CurrentPointIndex == 0 ? GetLastPointIndex() : 0;
		}
		else
		{
			NextPointIndex = CurrentPointIndex == GetLastPointIndex() ? 0 : GetLastPointIndex();
		}
	// Implement logic
		break;

	case ESplineAnimationMode::Manual:
		// No calculation required
		break;
	}
}

void USplineAnimationComponent::AnimateAlongSpline(const float Progress)
{
	if (!SplineComponent)
	{
		return;
	}

	const float Position = GetPositionAtSpline(CurrentPointIndex, NextPointIndex, Progress);
	const FVector NewLocation{
		SplineComponent->GetLocationAtDistanceAlongSpline(Position, ESplineCoordinateSpace::World)
	};

	GetOwner()->SetActorLocation(NewLocation + LocationOffset);
}

void USplineAnimationComponent::FinishAnimation()
{
	AnimationState = ESplineAnimationState::Idle;

	switch (AnimationMode)
	{
	case ESplineAnimationMode::Loop:
		if (bIsReversed)
		{
			CurrentPointIndex = NextPointIndex == 0 ? GetLastPointIndex() : 0;
		}
		else
		{
			CurrentPointIndex = NextPointIndex == GetLastPointIndex() ? 0 : GetLastPointIndex();
		}
		
		CalculateNextPointIndex();
		Start();
		break;

	case ESplineAnimationMode::PingPong:
		CurrentPointIndex = NextPointIndex;
		CalculateNextPointIndex();
		Start();
		break;

	default:
		CurrentPointIndex = NextPointIndex;
		break;
	}


	// Add logic
	// Call delegate
}

float USplineAnimationComponent::GetSplineDistanceAtPoint(const int32 PointIndex) const
{
	if (!SplineComponent) return -1.f;

	return SplineComponent->GetDistanceAlongSplineAtSplinePoint(PointIndex);
}

float USplineAnimationComponent::GetPositionAtSpline(const int32 CurrentIndex, const int32 NextIndex,
                                                     const float Progress) const
{
	if (!SplineComponent) return -1;

	const float Start = GetSplineDistanceAtPoint(CurrentIndex);
	const float Finish = GetSplineDistanceAtPoint(NextIndex);

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

void USplineAnimationComponent::CalculateAnimationTime(const int32 CurrentIndex, const int32 TargetIndex)
{
	if (!SplineComponent)
	{
		// Print error
		return;
	}

	if (bUseConstantSpeed)
	{
		const float StartDistance = GetSplineDistanceAtPoint(CurrentIndex);
		const float FinishDistance = GetSplineDistanceAtPoint(TargetIndex);
		const float DistanceBetweenPoints = FMath::Abs(FinishDistance - StartDistance);
		AnimationTime = DistanceBetweenPoints / ConstantSpeed;
	}
}

int32 USplineAnimationComponent::GetLastPointIndex() const
{
	return SplineComponent->GetNumberOfSplinePoints() - 1;
}
