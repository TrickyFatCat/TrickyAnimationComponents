// MIT License Copyright (c) Artyom "Tricky Fat Cat" Volkov


#include "TimelineAnimationComponent.h"
#include "Components/TimelineComponent.h"
#include "Curves/CurveFloat.h"

UTimelineAnimationComponent::UTimelineAnimationComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	UActorComponent::SetAutoActivate(true);

	AnimationTimeline = CreateDefaultSubobject<UTimelineComponent>("AnimationTimeline");
}

void UTimelineAnimationComponent::Activate(bool bReset)
{
	Super::Activate(bReset);

	if (bAnimateWholeActor)
	{
		TArray<USceneComponent*> Array{};
		SetAnimatedComponents(Array);
	}
}

void UTimelineAnimationComponent::BeginPlay()
{
	CurrentState = InitialState;

	if (AnimationTime <= 0.f)
	{
		AnimationTime = 1.f;
		LogWarning("Animation time can't be <= 0. It was set to 1.");
	}

	CalculatePlayRate();

	if (AnimationCurve)
	{
		FOnTimelineFloat AnimationProgress;
		AnimationProgress.BindUFunction(this, FName("AnimateTransform"));
		AnimationTimeline->AddInterpFloat(AnimationCurve, AnimationProgress);

		FOnTimelineEvent AnimationFinished;
		AnimationFinished.BindUFunction(this, FName("FinishAnimation"));
		AnimationTimeline->SetTimelineFinishedFunc(AnimationFinished);
	}

	if (CanPlayAnimation())
	{
		AnimateTransform(CurrentState == ETimelineAnimationState::End);
	}

	Super::BeginPlay();
}

bool UTimelineAnimationComponent::Start()
{
	if (!CanPlayAnimation())
	{
		return false;
	}

	if (CurrentState != ETimelineAnimationState::Transition && CurrentState != ETimelineAnimationState::Pause)
	{
		TargetState = CurrentState == ETimelineAnimationState::Begin
			              ? ETimelineAnimationState::End
			              : ETimelineAnimationState::Begin;

		TargetState == ETimelineAnimationState::End
			? AnimationTimeline->PlayFromStart()
			: AnimationTimeline->ReverseFromEnd();

		CurrentState = ETimelineAnimationState::Transition;
		OnAnimationStarted.Broadcast(TargetState);
		
		return true;
	}

	return false;
}

bool UTimelineAnimationComponent::Reverse()
{
	if (!CanPlayAnimation())
	{
		return false;
	}

	if (CurrentState == ETimelineAnimationState::Transition)
	{
		TargetState = TargetState == ETimelineAnimationState::Begin
			              ? ETimelineAnimationState::End
			              : ETimelineAnimationState::Begin;
		AnimationTimeline->Stop();
		TargetState == ETimelineAnimationState::End ? AnimationTimeline->Play() : AnimationTimeline->Reverse();
		OnAnimationReversed.Broadcast(TargetState);
		return true;
	}

	return false;
}

bool UTimelineAnimationComponent::Pause()
{
	if (CurrentState != ETimelineAnimationState::Transition)
	{
		LogWarning("Can't use the Pause() function if the current state isn't transition");
		return false;
	}
	
	CurrentState = ETimelineAnimationState::Pause;
	AnimationTimeline->Stop();
	OnAnimationPaused.Broadcast();
	return true;
}

bool UTimelineAnimationComponent::Resume()
{
	if (CurrentState != ETimelineAnimationState::Pause)
	{
		LogWarning("Can't use the Resume() function if the current state isn't pause.");
		return false;
	}

	CurrentState = ETimelineAnimationState::Transition;
	TargetState == ETimelineAnimationState::End ? AnimationTimeline->Play() : AnimationTimeline->Reverse();
	OnAnimationResumed.Broadcast();
	return true;
}

float UTimelineAnimationComponent::GetAnimationTime() const
{
	return AnimationTime;
}

void UTimelineAnimationComponent::SetAnimationTime(const float Value)
{
	if (Value <= 0.f || !AnimationCurve)
	{
		return;
	}

	AnimationTime = Value;
	CalculatePlayRate();
}

UCurveFloat* UTimelineAnimationComponent::GetAnimationCurve() const
{
	return AnimationCurve;
}

void UTimelineAnimationComponent::SetAnimationCurve(UCurveFloat* Value)
{
	if (!Value)
	{
		return;
	}

	AnimationCurve = Value;
	CalculatePlayRate();
}

float UTimelineAnimationComponent::GetAnimationProgress() const
{
	return AnimationTimeline->GetPlaybackPosition();
}

void UTimelineAnimationComponent::SetAnimatedComponents(TArray<USceneComponent*>& Components)
{
	AnimatedComponents.Empty();
	InitialTransforms.Empty();
	
	if (Components.Num() == 0)
	{
		return;
	}

	if (bAnimateWholeActor)
	{
		Components.Empty();
		Components.Emplace(GetOwner()->GetRootComponent());
	}

	for (auto Component : Components)
	{
		if (!Component || AnimatedComponents.Contains(Component))
		{
			continue;
		}

		AnimatedComponents.AddUnique(Component);
		InitialTransforms.Add(Component->GetRelativeTransform());
	}

	if (CanPlayAnimation() && !bAnimateWholeActor)
	{
		AnimateTransform(InitialState == ETimelineAnimationState::End);
	}
}

bool UTimelineAnimationComponent::CanPlayAnimation() const
{
	if (!AnimationCurve)
	{
		LogWarning("AnimationCurve isn't set, can't play the animation.");
		return false;
	}

	if (AnimatedComponents.Num() == 0)
	{
		LogWarning("AnimatedComponents array is empty, can't play the animation.");
		return false;
	}

	if (TransformOffsets.Num() == 0 || TransformOffsets.Num() != AnimatedComponents.Num())
	{
		LogWarning("TransformOffsets array either empty or don't have enough values to start play the animation.");
		return false;
	}
	return true;
}

ETimelineAnimationState UTimelineAnimationComponent::GetCurrentState() const
{
	return CurrentState;
}

ETimelineAnimationState UTimelineAnimationComponent::GetTargetState() const
{
	return TargetState;
}

bool UTimelineAnimationComponent::IsPlaying() const
{
	return CurrentState == ETimelineAnimationState::Transition;
}

void UTimelineAnimationComponent::GetTransformOffsets(TArray<FTransform>& Offsets) const
{
	Offsets = TransformOffsets;
}

void UTimelineAnimationComponent::SetTransformOffsets(const TArray<FTransform>& Offsets)
{
	TransformOffsets = Offsets;
}

void UTimelineAnimationComponent::AnimateTransform(const float Progress)
{
	if (!CanPlayAnimation())
	{
		return;
	}

	for (int32 i = 0; i < AnimatedComponents.Num(); ++i)
	{
		FTransform NewTransform = InitialTransforms[i];
		FTransform TargetTransform;
		TargetTransform.SetLocation(TransformOffsets[i].GetLocation());
		TargetTransform.SetRotation(TransformOffsets[i].GetRotation());
		TargetTransform.SetScale3D(TransformOffsets[i].GetScale3D());

		if (TargetTransform.GetLocation() != FVector::ZeroVector)
		{
			NewTransform.SetLocation(NewTransform.GetLocation() + TargetTransform.GetLocation() * Progress);
		}

		if (TargetTransform.GetRotation() != FRotator::ZeroRotator.Quaternion())
		{
			FQuat NewRotation{
					FRotator(NewTransform.GetRotation().Rotator() + TargetTransform.GetRotation().Rotator() *
					         Progress).Quaternion()
			};
			NewTransform.SetRotation(NewRotation);
		}

		if (TargetTransform.GetScale3D() != FVector::ZeroVector)
		{
			NewTransform.SetScale3D(NewTransform.GetScale3D() + TargetTransform.GetScale3D() * Progress);
		}

		AnimatedComponents[i]->SetRelativeTransform(NewTransform);
	}
}

void UTimelineAnimationComponent::FinishAnimation()
{
	CurrentState = TargetState;
	OnAnimationFinished.Broadcast(CurrentState);
}

void UTimelineAnimationComponent::CalculatePlayRate() const
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
		MaxTime = 1.f;
		LogWarning("Length of the chosen curve is <= 0.");
	}

	AnimationTimeline->SetPlayRate(MaxTime / AnimationTime);
}

void UTimelineAnimationComponent::LogWarning(const FString& Message) const
{
	if (!GetWorld())
	{
		return;
	}

	const FString ErrorMessage{FString::Printf(TEXT("%s | Actor: %s"), *Message, *GetOwner()->GetName())};
	UE_LOG(LogTimelineAnimationComponent, Warning, TEXT("%s"), *ErrorMessage);
}
