// MIT License Copyright (c) Artyom "Tricky Fat Cat" Volkov

#include "EasingAnimationSceneComponent.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"

UEasingAnimationSceneComponent::UEasingAnimationSceneComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	UActorComponent::SetComponentTickEnabled(false);
	bWantsInitializeComponent = true;
}

void UEasingAnimationSceneComponent::InitializeComponent()
{
	Super::InitializeComponent();
}

void UEasingAnimationSceneComponent::BeginPlay()
{
	Super::BeginPlay();

	InitialLocation = GetRelativeLocation();
	InitialRotation = GetRelativeRotation();
	InitialScale = GetRelativeScale3D();
	
	if (bAutoPlay)
	{
		bPlayFromEnd ? PlayFromEnd() : PlayFromStart();
	}
}

void UEasingAnimationSceneComponent::TickComponent(float DeltaTime,
                                                   ELevelTick TickType,
                                                   FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bIsPlaying)
	{
		const float CurrentTime = GetWorld()->GetTimeSeconds() - LaunchTime;

		if (CurrentTime < Duration)
		{
			const float Alpha = CurrentTime / Duration;
			if (bAnimateLocation)
			{
				FVector NewLocation;
				EaseVector(NewLocation, StartLocation, EndLocation, Alpha);
				SetRelativeLocation(NewLocation);
			}

			if (bAnimateRotation)
			{
				FRotator NewRotation;
				EaseRotator(NewRotation, StartRotation, EndRotation, Alpha);
				SetRelativeRotation(NewRotation);
			}

			if (bAnimateScale)
			{
				FVector NewScale;
				EaseVector(NewScale, StartScale, EndScale, Alpha);
				SetRelativeScale3D(NewScale);
			}
		}
		else
		{
			Finish();
		}
	}
}

bool UEasingAnimationSceneComponent::GetIsPlaying() const
{
	return bIsPlaying;
}

bool UEasingAnimationSceneComponent::PlayFromStart()
{
	if (bIsPlaying)
	{
		return false;
	}

	if (Duration <= 0.f)
	{
		UE_LOG(LogTemp, Error, TEXT("Ease animation duration is <= 0."));
		return false;
	}

	LaunchTime = GetWorld()->GetTimeSeconds();
	
	StartLocation = InitialLocation;
	StartRotation = InitialRotation;
	StartScale = InitialScale;

	EndLocation = TargetLocation + StartLocation;
	EndRotation = TargetRotation + StartRotation;
	EndScale = TargetScale + StartScale;

	bIsPlaying = true;
	SetComponentTickEnabled(true);
	return true;
}

bool UEasingAnimationSceneComponent::PlayFromEnd()
{
	if (bIsPlaying)
	{
		return false;
	}

	if (Duration <= 0.f)
	{
		UE_LOG(LogTemp, Error, TEXT("Ease animation duration is <= 0."));
		return false;
	}

	LaunchTime = GetWorld()->GetTimeSeconds();

	StartLocation = TargetLocation;
	StartRotation = TargetRotation;
	StartScale = TargetScale;

	EndLocation = InitialLocation;
	EndRotation = InitialRotation;
	EndScale = InitialScale;
	
	bIsPlaying = true;
	SetComponentTickEnabled(true);
	return true;
}

bool UEasingAnimationSceneComponent::Stop()
{
	if (!bIsPlaying)
	{
		return false;
	}

	bIsPlaying = false;
	SetComponentTickEnabled(false);
	return true;
}

float UEasingAnimationSceneComponent::GetEaseDuration() const
{
	return Duration;
}

void UEasingAnimationSceneComponent::SetEaseDuration(const float Value)
{
	if (Value < 0.f)
	{
		return;
	}

	Duration = Value;
}

FVector UEasingAnimationSceneComponent::GetTargetLocation() const
{
	return TargetLocation;
}

void UEasingAnimationSceneComponent::SetTargetLocation(const FVector& Value)
{
	TargetLocation = Value;
}

FRotator UEasingAnimationSceneComponent::GetTargetRotation() const
{
	return TargetRotation;
}

void UEasingAnimationSceneComponent::SetTargetRotation(const FRotator& Value)
{
	TargetRotation = Value;
}

FVector UEasingAnimationSceneComponent::GetTargetScale() const
{
	return TargetScale;
}

void UEasingAnimationSceneComponent::SetTargetScale(const FVector& Value)
{
	TargetScale = Value;
}

void UEasingAnimationSceneComponent::Finish()
{
	OnAnimationFinished.Broadcast();

	switch (AnimationBehavior)
	{
	case EEaseAnimBehavior::Normal:
		bIsPlaying = false;
		SetComponentTickEnabled(false);
		break;

	case EEaseAnimBehavior::Loop:
		SetRelativeLocation(StartLocation);
		SetRelativeRotation(StartRotation);
		SetRelativeScale3D(StartScale);
		LaunchTime = GetWorld()->GetTimeSeconds();
		break;

	case EEaseAnimBehavior::AdditiveLoop:
		StartLocation = EndLocation;
		StartRotation = EndRotation;
		StartScale = EndScale;

		EndLocation = StartLocation + TargetLocation;
		EndRotation = StartRotation + TargetRotation;
		EndScale = StartScale + TargetScale;

		LaunchTime = GetWorld()->GetTimeSeconds();
		break;

	case EEaseAnimBehavior::PingPong:
		UTrickyAnimationComponentsLibrary::SwapValues<FVector>(StartLocation, EndLocation);
		UTrickyAnimationComponentsLibrary::SwapValues<FRotator>(StartRotation, EndRotation);
		UTrickyAnimationComponentsLibrary::SwapValues<FVector>(StartScale, EndScale);
		LaunchTime = GetWorld()->GetTimeSeconds();
		break;
	}
}

void UEasingAnimationSceneComponent::EaseVector(FVector& Value,
                                                const FVector& InitialValue,
                                                const FVector& TargetValue,
                                                const float Alpha) const
{
	UTrickyAnimationComponentsLibrary::EaseVector(Value,
	                                              InitialValue,
	                                              TargetValue,
	                                              Alpha,
	                                              EaseFunction,
	                                              BlendExp,
	                                              Steps);
}

void UEasingAnimationSceneComponent::EaseRotator(FRotator& Value,
                                                 const FRotator& InitialValue,
                                                 const FRotator& TargetValue,
                                                 const float Alpha) const
{
	UTrickyAnimationComponentsLibrary::EaseRotator(Value,
	                                               InitialValue,
	                                               TargetValue,
	                                               Alpha,
	                                               EaseFunction,
	                                               BlendExp,
	                                               Steps);
}
