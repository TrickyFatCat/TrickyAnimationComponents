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

	if (!IsValid(SplineActor))
	{
		LogWarning("SplineActor isn't set for an spline animation component.");
	}
	else
	{
		SplineComponent = SplineActor->FindComponentByClass<USplineComponent>();

		if (HasSplineComponent())
		{
			if (StartPointIndex > GetLastPointIndex())
			{
				StartPointIndex = 0;
				LogWarning("Incorrect StartPointIndex value, it can't be <= 0 or > LastPointIndex. Reset it to 0.");
			}

			CurrentPointIndex = StartPointIndex;
			CalculateNextPointIndex();
			CalculateAnimationTime(CurrentPointIndex, NextPointIndex);
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


void USplineAnimationComponent::TickComponent(float DeltaTime,
                                              ELevelTick TickType,
                                              FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void USplineAnimationComponent::Start()
{
	if (AnimationMode == ESplineAnimationMode::Manual)
	{
		LogWarning("Can't use the Start() function in the manual animation mode.");
		return;
	}

	if (AnimationState != ESplineAnimationState::Idle)
	{
		LogWarning("Can't use the Start() function when the component not in the idle state.");
		return;
	}

	if (bStopAtPoints && bWaitAtStart)
	{
		StartWaitTimer();
		return;
	}

	CalculateAnimationTime(CurrentPointIndex, NextPointIndex);
	CalculatePlayRate();
	AnimationTimeline->PlayFromStart();
	AnimationState = ESplineAnimationState::Transition;
	OnAnimationStarted.Broadcast();
}

void USplineAnimationComponent::Stop()
{
	bMustStop = true;

	if (GetWorld() && AnimationState == ESplineAnimationState::Wait)
	{
		GetWorld()->GetTimerManager().ClearTimer(WaitTimerHandle);
		FinishAnimation();
	}
}

void USplineAnimationComponent::MoveTo(const int32 PointIndex)
{
	if (AnimationMode != ESplineAnimationMode::Manual)
	{
		LogWarning("Can't use the MoveTo() function while the component isn't in manual mode");
		return;
	}

	if (PointIndex < 0 || PointIndex > GetLastPointIndex())
	{
		LogWarning(FString::Printf(TEXT("Can't move the actor to the point index %d"), PointIndex));
		return;
	}

	NextPointIndex = PointIndex;
	CalculateAnimationTime(CurrentPointIndex, NextPointIndex);
	CalculatePlayRate();
	AnimationTimeline->PlayFromStart();
	AnimationState = ESplineAnimationState::Transition;
	OnAnimationStarted.Broadcast();
}

void USplineAnimationComponent::Pause()
{
	if (AnimationState != ESplineAnimationState::Transition)
	{
		LogWarning("Can't use the Pause() function while the component isn't in the transition state.");
		return;
	}

	AnimationTimeline->Stop();
	AnimationState = ESplineAnimationState::Pause;
	OnAnimationPaused.Broadcast();
}

void USplineAnimationComponent::Resume()
{
	if (AnimationState != ESplineAnimationState::Pause)
	{
		LogWarning("Can't use the Resume() function while the component isn't in the pause state");
		return;
	}

	AnimationTimeline->Play();
	AnimationState = ESplineAnimationState::Transition;
	OnAnimationResumed.Broadcast();
}

UCurveFloat* USplineAnimationComponent::GetAnimationCurve() const
{
	return AnimationCurve;
}

void USplineAnimationComponent::SetAnimationCurve(UCurveFloat* Value)
{
	AnimationCurve = Value;
}

bool USplineAnimationComponent::GetIsReversed() const
{
	return bIsReversed;
}

void USplineAnimationComponent::SetIsReversed(const bool Value)
{
	if (bIsReversed == Value)
	{
		return;
	}

	bIsReversed = Value;
	CalculateNextPointIndex();
	CalculateAnimationTime(CurrentPointIndex, NextPointIndex);
	CalculatePlayRate();
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
		LogWarning("Insufficient new value of the AnimationTime variable. It's <= 0");
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
		CalculateAnimationTime(CurrentPointIndex, NextPointIndex);
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
		LogWarning("Insufficient new value of the ConstantSpeed variable. It's <= 0");
		return;
	}

	ConstantSpeed = Value;
	CalculateAnimationTime(CurrentPointIndex, NextPointIndex);
	CalculatePlayRate();
}

void USplineAnimationComponent::CalculateNextPointIndex()
{
	switch (AnimationMode)
	{
	case ESplineAnimationMode::OneWay:
		if (bStopAtPoints)
		{
			NextPointIndex = bIsReversed ? CurrentPointIndex - 1 : CurrentPointIndex + 1;
			NextPointIndex = FMath::Clamp(NextPointIndex, 0, GetLastPointIndex());
		}
		else
		{
			NextPointIndex = bIsReversed ? 0 : GetLastPointIndex();
		}
		break;

	case ESplineAnimationMode::Loop:
		NextPointIndex = bIsReversed ? 0 : GetLastPointIndex();

		if (bStopAtPoints)
		{
			NextPointIndex = bIsReversed ? CurrentPointIndex - 1 : CurrentPointIndex + 1;
			NextPointIndex = FMath::Clamp(NextPointIndex, 0, GetLastPointIndex());
		}
		break;

	case ESplineAnimationMode::PingPong:
		if (bStopAtPoints)
		{
			if (CurrentPointIndex == 0)
			{
				bIsReversed = false;
			}
			else if (CurrentPointIndex == GetLastPointIndex())
			{
				bIsReversed = true;
			}

			NextPointIndex = bIsReversed ? CurrentPointIndex - 1 : CurrentPointIndex + 1;
			NextPointIndex = FMath::Clamp(NextPointIndex, 0, GetLastPointIndex());
		}
		else
		{
			if (bIsReversed)
			{
				NextPointIndex = CurrentPointIndex == 0 ? GetLastPointIndex() : 0;
			}
			else
			{
				NextPointIndex = CurrentPointIndex == GetLastPointIndex() ? 0 : GetLastPointIndex();
			}
		}
		break;

	case ESplineAnimationMode::Manual:
		break;
	}
}

void USplineAnimationComponent::AnimateAlongSpline(const float Progress) const
{
	if (!HasSplineComponent())
	{
		return;
	}

	MoveAlongSpline(Progress);
	RotateAlongSpline(Progress);
	ScaleAlongSpline(Progress);
}

void USplineAnimationComponent::MoveAlongSpline(const float Progress) const
{
	const float Position = GetPositionAtSpline(CurrentPointIndex, NextPointIndex, Progress);
	const FVector NewLocation{
			SplineComponent->GetLocationAtDistanceAlongSpline(Position, ESplineCoordinateSpace::World)
	};

	GetOwner()->SetActorLocation(NewLocation + LocationOffset);
}

void USplineAnimationComponent::RotateAlongSpline(const float Progress) const
{
	if (InheritRotation.bX || InheritRotation.bY || InheritRotation.bZ)
	{
		const FRotator CurrentRotation{GetOwner()->GetActorRotation()};
		const float Position = GetPositionAtSpline(CurrentPointIndex, NextPointIndex, Progress);
		const FRotator RotationAlongSpline{
				SplineComponent->GetRotationAtDistanceAlongSpline(Position, ESplineCoordinateSpace::World)
		};

		const float NewRoll = InheritRotation.bX ? RotationAlongSpline.Roll : CurrentRotation.Roll;
		const float NewPitch = InheritRotation.bY ? RotationAlongSpline.Pitch : CurrentRotation.Pitch;
		const float NewYaw = InheritRotation.bZ ? RotationAlongSpline.Yaw : CurrentRotation.Yaw;

		GetOwner()->SetActorRotation(FRotator{NewPitch, NewYaw, NewRoll});
	}
}

void USplineAnimationComponent::ScaleAlongSpline(const float Progress) const
{
	if (InheritScale.bX || InheritScale.bY || InheritScale.bZ)
	{
		const FVector CurrentScale{GetOwner()->GetActorScale3D()};
		const float Position = GetPositionAtSpline(CurrentPointIndex, NextPointIndex, Progress);
		const FVector ScaleAlongSpline{SplineComponent->GetScaleAtDistanceAlongSpline(Position)};

		const float NewScaleX = InheritScale.bX ? ScaleAlongSpline.X : CurrentScale.X;
		const float NewScaleY = InheritScale.bY ? ScaleAlongSpline.Y : CurrentScale.Y;
		const float NewScaleZ = InheritScale.bZ ? ScaleAlongSpline.Z : CurrentScale.Z;

		GetOwner()->SetActorScale3D(FVector{NewScaleX, NewScaleY, NewScaleZ});
	}
}

void USplineAnimationComponent::FinishAnimation()
{
	AnimationState = ESplineAnimationState::Idle;

	if (bMustStop)
	{
		CurrentPointIndex = NextPointIndex;
		AnimationTimeline->Stop();
		OnAnimationStopped.Broadcast(CurrentPointIndex);
		return;
	}

	switch (AnimationMode)
	{
	case ESplineAnimationMode::OneWay:
		if (bStopAtPoints)
		{
			CurrentPointIndex = NextPointIndex;
			CalculateNextPointIndex();
			StartWaitTimer();
		}

		OnAnimationStopped.Broadcast(CurrentPointIndex);
		break;

	case ESplineAnimationMode::Loop:
		if (bStopAtPoints)
		{
			CurrentPointIndex = NextPointIndex;

			if (CurrentPointIndex == 0)
			{
				CurrentPointIndex = GetLastPointIndex();
			}
			else if (CurrentPointIndex == GetLastPointIndex())
			{
				CurrentPointIndex = 0;
			}

			OnAnimationStopped.Broadcast(CurrentPointIndex);
		}
		else
		{
			if (bIsReversed)
			{
				CurrentPointIndex = NextPointIndex == 0 ? GetLastPointIndex() : 0;
			}
			else
			{
				CurrentPointIndex = NextPointIndex == GetLastPointIndex() ? 0 : GetLastPointIndex();
			}
		}

		CalculateNextPointIndex();
		bStopAtPoints ? StartWaitTimer() : Start();
		break;

	case ESplineAnimationMode::PingPong:
		CurrentPointIndex = NextPointIndex;
		CalculateNextPointIndex();

		if (bStopAtPoints)
		{
			StartWaitTimer();
			OnAnimationStopped.Broadcast(CurrentPointIndex);
		}
		else
		{
			Continue();
		}

		break;

	case ESplineAnimationMode::Manual:
		CurrentPointIndex = NextPointIndex;
		break;
	}
}

float USplineAnimationComponent::GetSplineDistanceAtPoint(const int32 PointIndex) const
{
	if (!HasSplineComponent())
	{
		return 0.f;
	}

	return SplineComponent->GetDistanceAlongSplineAtSplinePoint(PointIndex);
}

float USplineAnimationComponent::GetPositionAtSpline(const int32 CurrentIndex,
                                                     const int32 NextIndex,
                                                     const float Progress) const
{
	if (!HasSplineComponent())
	{
		return 0.f;
	}

	const float Start = GetSplineDistanceAtPoint(CurrentIndex);
	const float Finish = GetSplineDistanceAtPoint(NextIndex);

	return FMath::Lerp(Start, Finish, Progress);
}

void USplineAnimationComponent::CalculatePlayRate() const
{
	if (!AnimationCurve)
	{
		LogWarning("AnimationCurve wasn't set.");
		return;
	}

	float MinTime = 0.f;
	float MaxTime = 0.f;

	AnimationCurve->GetTimeRange(MinTime, MaxTime);

	if (MaxTime <= 0.f)
	{
		LogWarning("The length of AnimationCurve is <= 0.");
		MaxTime = 1.f;
	}

	AnimationTimeline->SetPlayRate(MaxTime / AnimationTime);
}

void USplineAnimationComponent::CalculateAnimationTime(const int32 CurrentIndex, const int32 TargetIndex)
{
	if (!HasSplineComponent())
	{
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
	return SplineComponent->GetNumberOfSplinePoints() - !SplineComponent->IsClosedLoop();
}

void USplineAnimationComponent::StartWaitTimer()
{
	if (!bStopAtPoints)
	{
		return;
	}

	const UWorld* World = GetWorld();

	if (World)
	{
		World->GetTimerManager().SetTimer(WaitTimerHandle, this, &USplineAnimationComponent::Continue, WaitTime);
		AnimationState = ESplineAnimationState::Wait;
	}
}

void USplineAnimationComponent::Continue()
{
	if (AnimationState != ESplineAnimationState::Wait)
	{
		LogWarning("Can't continue playing animation");
		return;
	}

	CalculateAnimationTime(CurrentPointIndex, NextPointIndex);
	CalculatePlayRate();
	AnimationTimeline->PlayFromStart();
	AnimationState = ESplineAnimationState::Transition;

	if (bStopAtPoints)
	{
		OnAnimationResumed.Broadcast();
	}
}

void USplineAnimationComponent::LogWarning(const FString& Message) const
{
	if (!GetWorld())
	{
		return;
	}

	const FString ErrorMessage{FString::Printf(TEXT("%s | Actor: %s"), *Message, *GetOwner()->GetName())};
	UE_LOG(LogSplineAnimationComponent, Error, TEXT("%s"), *ErrorMessage);
}

bool USplineAnimationComponent::HasSplineComponent() const
{
	if (!IsValid(SplineComponent))
	{
		LogWarning("Spline component wasn't found in chosen SplineActor.");
	}

	return IsValid(SplineComponent);
}
