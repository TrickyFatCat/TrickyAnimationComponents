// MIT License Copyright. Created by Artyom "Tricky Fat Cat" Volkov

#include "EasingAnimationSceneComponent.h"
#include "GameFramework/Actor.h"

UEasingAnimationSceneComponent::UEasingAnimationSceneComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	UActorComponent::SetComponentTickEnabled(false);
}

void UEasingAnimationSceneComponent::BeginPlay()
{
	Super::BeginPlay();

	if (bStartOnBeginPlay)
	{
		Start();
	}
}

void UEasingAnimationSceneComponent::TickComponent(float DeltaTime,
                                                   ELevelTick TickType,
                                                   FActorComponentTickFunction* ThisTickFunction)
{
	if (bIsPlaying)
	{
		if (bAnimateLocation)
		{
			FVector NewLocation;
			NewLocation.X = EaseFloat(InitialLocation.X, TargetLocation.X);
			NewLocation.Y = EaseFloat(InitialLocation.Y, TargetLocation.Y);
			NewLocation.Z = EaseFloat(InitialLocation.Z, TargetLocation.Z);
			SetRelativeLocation(NewLocation);
		}

		if (bAnimateRotation)
		{
			FRotator NewRotation;
			NewRotation.Pitch = EaseFloat(InitialRotation.Pitch, TargetRotation.Pitch);
			NewRotation.Yaw = EaseFloat(InitialRotation.Yaw, TargetRotation.Yaw);
			NewRotation.Roll = EaseFloat(InitialRotation.Roll, TargetRotation.Roll);
			SetRelativeRotation(NewRotation);
		}

		if (bAnimateScale)
		{
			FVector NewScale;
			NewScale.X = EaseFloat(InitialScale.X, TargetScale.X);
			NewScale.Y = EaseFloat(InitialScale.Y, TargetScale.Y);
			NewScale.Z = EaseFloat(InitialScale.Z, TargetScale.Z);
			SetRelativeScale3D(NewScale);
		}
	}

	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

bool UEasingAnimationSceneComponent::GetIsPlaying() const
{
	return bIsPlaying;
}

void UEasingAnimationSceneComponent::Start()
{
	if (bIsPlaying)
	{
		return;
	}

	if (Duration <= 0.f)
	{
		UE_LOG(LogTemp, Error, TEXT("Ease animation duration is <= 0."));
	}

	bIsPlaying = true;
	SetComponentTickEnabled(true);
	LaunchTime = GetWorld()->GetTimeSeconds();
	InitialLocation = GetRelativeLocation();
	InitialRotation = GetRelativeRotation();
	InitialScale = GetRelativeScale3D();	
	// SetInitialValues();
	// CalculateTargetValues();
	OnAnimationStarted.Broadcast();
}

void UEasingAnimationSceneComponent::Stop()
{
	if (!bIsPlaying)
	{
		return;
	}

	bIsPlaying = false;
	SetComponentTickEnabled(false);
	OnAnimationStopped.Broadcast();
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

float UEasingAnimationSceneComponent::EaseFloat(const float InitialValue,
                                                const float TargetValue)
{
	const float CurrentTime = GetWorld()->GetTimeSeconds();

	if (CurrentTime - LaunchTime < Duration)
	{
		const float Alpha = (CurrentTime - LaunchTime) / Duration;
		return UKismetMathLibrary::Ease(InitialValue,
		                                TargetValue,
		                                Alpha,
		                                EaseFunction,
		                                Exponent,
		                                SubStep);
	}

	OnAnimationFinished.Broadcast();

	if (bIsLooping)
	{
		LaunchTime = GetWorld()->GetTimeSeconds();
		
		switch(AnimationBehavior)
		{
		case EEaseAnimBehavior::Normal:
			SetRelativeLocation(InitialLocation);
			SetRelativeRotation(InitialRotation);
			SetRelativeScale3D(InitialScale);
			break;

		case EEaseAnimBehavior::PingPong:
			SwapValues<FVector>(InitialLocation, TargetLocation);
			SwapValues<FRotator>(InitialRotation, TargetRotation);
			SwapValues<FVector>(InitialScale, TargetScale);
			break;
		}
	}
	else
	{
		bIsPlaying = false;
		SetComponentTickEnabled(false);
	}

	return TargetValue;
}