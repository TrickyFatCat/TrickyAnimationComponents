// MIT License Copyright (c) 2022 Artyom "Tricky Fat Cat" Volkov


#include "TimelineAnimationComponent.h"

#include "Components/TimelineComponent.h"


UTimelineAnimationComponent::UTimelineAnimationComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	Timeline = CreateDefaultSubobject<UTimelineComponent>("Timeline");
}


void UTimelineAnimationComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentState = InitialState;
}


void UTimelineAnimationComponent::Start()
{
	if (CurrentState != ETimelineAnimationState::Transition)
	{
		TargetState = CurrentState == ETimelineAnimationState::Start
			              ? ETimelineAnimationState::End
			              : ETimelineAnimationState::Start;

		//Start timeline here;
		CurrentState = ETimelineAnimationState::Transition;
		OnAnimationStarted.Broadcast(TargetState);
	}
}

void UTimelineAnimationComponent::Reverse()
{
	if (CurrentState == ETimelineAnimationState::Transition && bIsReversible)
	{
		TargetState = TargetState == ETimelineAnimationState::Start
			              ? ETimelineAnimationState::End
			              : ETimelineAnimationState::Start;
		// Reverse timeline here;
		OnAnimationReversed.Broadcast(TargetState);
	}
}

void UTimelineAnimationComponent::Stop()
{
	// Do checks
	// Do logic
	OnAnimationStopped.Broadcast();
}

void UTimelineAnimationComponent::Resume()
{
	// Do checks
	// Do logic
	OnAnimationResumed.Broadcast();
}

void UTimelineAnimationComponent::FinishAnimation()
{
	CurrentState = TargetState;
	OnAnimationFinished.Broadcast(CurrentState);
}
