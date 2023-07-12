// MIT License Copyright (c) Artyom "Tricky Fat Cat" Volkov

#include "EaseAnimationComponent.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"

UEaseAnimationComponent::UEaseAnimationComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	UActorComponent::SetComponentTickEnabled(false);
	bWantsInitializeComponent = true;
}

void UEaseAnimationComponent::InitializeComponent()
{
	Super::InitializeComponent();
}

void UEaseAnimationComponent::BeginPlay()
{
	Super::BeginPlay();

	InitialLocation = GetOwner()->GetActorLocation();
	InitialRotation = GetOwner()->GetActorRotation();
	InitialScale = GetOwner()->GetActorScale();

	if (bAutoPlay)
	{
		bPlayFromEnd ? PlayFromEnd() : PlayFromStart();
	}
}

void UEaseAnimationComponent::TickComponent(float DeltaTime,
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
				UTrickyEasingLibrary::EaseVector(NewLocation, StartLocation, EndLocation, EaseFunction, Alpha);
				GetOwner()->SetActorLocation(NewLocation);
			}

			if (bAnimateRotation)
			{
				FRotator NewRotation;
				UTrickyEasingLibrary::EaseRotator(NewRotation, StartRotation, EndRotation, EaseFunction, Alpha);
				GetOwner()->SetActorRotation(NewRotation);
			}

			if (bAnimateScale)
			{
				FVector NewScale;
				UTrickyEasingLibrary::EaseVector(NewScale, StartScale, EndScale, EaseFunction, Alpha);
				GetOwner()->SetActorScale3D(NewScale);
			}
		}
		else
		{
			Finish();
		}
	}
}

bool UEaseAnimationComponent::GetIsPlaying() const
{
	return bIsPlaying;
}

bool UEaseAnimationComponent::PlayFromStart()
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

bool UEaseAnimationComponent::PlayFromEnd()
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

bool UEaseAnimationComponent::Stop()
{
	if (!bIsPlaying)
	{
		return false;
	}

	bIsPlaying = false;
	SetComponentTickEnabled(false);
	return true;
}

float UEaseAnimationComponent::GetEaseDuration() const
{
	return Duration;
}

void UEaseAnimationComponent::SetEaseDuration(const float Value)
{
	if (Value < 0.f)
	{
		return;
	}

	Duration = Value;
}

FVector UEaseAnimationComponent::GetTargetLocation() const
{
	return TargetLocation;
}

void UEaseAnimationComponent::SetTargetLocation(const FVector& Value)
{
	TargetLocation = Value;
}

FRotator UEaseAnimationComponent::GetTargetRotation() const
{
	return TargetRotation;
}

void UEaseAnimationComponent::SetTargetRotation(const FRotator& Value)
{
	TargetRotation = Value;
}

FVector UEaseAnimationComponent::GetTargetScale() const
{
	return TargetScale;
}

void UEaseAnimationComponent::SetTargetScale(const FVector& Value)
{
	TargetScale = Value;
}

void UEaseAnimationComponent::Finish()
{
	OnAnimationFinished.Broadcast();

	switch (AnimationBehavior)
	{
	case EEaseAnimBehavior::Normal:
		bIsPlaying = false;
		SetComponentTickEnabled(false);
		break;

	case EEaseAnimBehavior::Loop:
		GetOwner()->SetActorLocation(StartLocation);
		GetOwner()->SetActorRotation(StartRotation);
		GetOwner()->SetActorScale3D(StartScale);
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
