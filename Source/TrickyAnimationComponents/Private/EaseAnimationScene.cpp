// MIT License Copyright (c) Artyom "Tricky Fat Cat" Volkov

#include "EaseAnimationScene.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "Libraries/TrickyEasingLibrary.h"

UEaseAnimationScene::UEaseAnimationScene()
{
	PrimaryComponentTick.bCanEverTick = true;
	UActorComponent::SetComponentTickEnabled(false);
	bWantsInitializeComponent = true;
}

void UEaseAnimationScene::InitializeComponent()
{
	Super::InitializeComponent();
}

void UEaseAnimationScene::BeginPlay()
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

void UEaseAnimationScene::TickComponent(float DeltaTime,
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
				SetRelativeLocation(NewLocation);
			}

			if (bAnimateRotation)
			{
				FRotator NewRotation;
				UTrickyEasingLibrary::EaseRotator(NewRotation, StartRotation, EndRotation, EaseFunction, Alpha);
				SetRelativeRotation(NewRotation);
			}

			if (bAnimateScale)
			{
				FVector NewScale;
				UTrickyEasingLibrary::EaseVector(NewScale, StartScale, EndScale, EaseFunction, Alpha);
				SetRelativeScale3D(NewScale);
			}
		}
		else
		{
			Finish();
		}
	}
}

bool UEaseAnimationScene::GetIsPlaying() const
{
	return bIsPlaying;
}

bool UEaseAnimationScene::PlayFromStart()
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

bool UEaseAnimationScene::PlayFromEnd()
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

bool UEaseAnimationScene::Stop()
{
	if (!bIsPlaying)
	{
		return false;
	}

	bIsPlaying = false;
	SetComponentTickEnabled(false);
	return true;
}

float UEaseAnimationScene::GetEaseDuration() const
{
	return Duration;
}

void UEaseAnimationScene::SetEaseDuration(const float Value)
{
	if (Value < 0.f)
	{
		return;
	}

	Duration = Value;
}

FVector UEaseAnimationScene::GetTargetLocation() const
{
	return TargetLocation;
}

void UEaseAnimationScene::SetTargetLocation(const FVector& Value)
{
	TargetLocation = Value;
}

FRotator UEaseAnimationScene::GetTargetRotation() const
{
	return TargetRotation;
}

void UEaseAnimationScene::SetTargetRotation(const FRotator& Value)
{
	TargetRotation = Value;
}

FVector UEaseAnimationScene::GetTargetScale() const
{
	return TargetScale;
}

void UEaseAnimationScene::SetTargetScale(const FVector& Value)
{
	TargetScale = Value;
}

void UEaseAnimationScene::Finish()
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