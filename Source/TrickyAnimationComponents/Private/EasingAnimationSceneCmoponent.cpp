// MIT License Copyright. Created by Artyom "Tricky Fat Cat" Volkov

#include <propsys.h>

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
		StartAnimation();
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

void UEasingAnimationSceneComponent::StartAnimation()
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

void UEasingAnimationSceneComponent::StopAnimation()
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

FVector UEasingAnimationSceneComponent::GetLocation() const
{
	return TargetLocation;
}

void UEasingAnimationSceneComponent::SetLocation(const FVector& Value)
{
	TargetLocation = Value;

	if (AnimationBehavior == EEaseAnimBehavior::Normal)
	{
		TargetLocation = TargetLocation;
	}
}

FRotator UEasingAnimationSceneComponent::GetRotation() const
{
	return TargetRotation;
}

void UEasingAnimationSceneComponent::SetRotation(const FRotator& Value)
{
	TargetRotation = Value;

	if (AnimationBehavior == EEaseAnimBehavior::Normal)
	{
		TargetRotation = TargetRotation;
	}
}

FVector UEasingAnimationSceneComponent::GetScale() const
{
	return TargetScale;
}

void UEasingAnimationSceneComponent::SetScale(const FVector& Value)
{
	TargetScale = Value;

	if (AnimationBehavior == EEaseAnimBehavior::Normal)
	{
		TargetScale = TargetScale;
	}
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
			SwitchValues<FVector>(InitialLocation, TargetLocation);
			SwitchValues<FRotator>(InitialRotation, TargetRotation);
			SwitchValues<FVector>(InitialScale, TargetScale);
			break;
		}
	}
	else
	{
		bIsPlaying = false;
		SetComponentTickEnabled(false);
	}
	// switch (AnimationBehavior)
	// {
	// case EEaseAnimBehavior::Normal:
	// 	break;
	//
	// case EEaseAnimBehavior::Loop:
	// 	SetInitialValues();
	// 	CalculateTargetValues();
	// 	break;
	//
	// case EEaseAnimBehavior::PingPong:
	// 	PinPongDirection *= -1;
	// 	SetInitialValues();
	// 	CalculateTargetValues();
	// 	break;
	// }


	return TargetValue;
}

// void UEasingAnimationSceneComponent::SetInitialValues()
// {

// }

// void UEasingAnimationSceneComponent::CalculateTargetValues()
// {
	// switch (AnimationBehavior)
	// {
	// case EEaseAnimBehavior::Normal:
	// 	TargetLocation = Location;
	// 	TargetRotation = Rotation;
	// 	TargetScale = Scale;
	// 	break;
	//
	// case EEaseAnimBehavior::Loop:
	// 	TargetLocation = InitialLocation + Location;
	// 	TargetRotation = InitialRotation + Rotation;
	// 	TargetScale = InitialScale + Scale;
	// 	break;
	//
	// case EEaseAnimBehavior::PingPong:
	// 	TargetLocation = InitialLocation + Location * PinPongDirection;
	// 	TargetRotation = InitialRotation + Rotation * PinPongDirection;
	// 	TargetScale = InitialScale + Scale * PinPongDirection;
	// }
// }
