// MIT License Copyright. Created by Artyom "Tricky Fat Cat" Volkov

#include "EaseAnimationComponent.h"
#include "GameFramework/Actor.h"

UEaseAnimationComponent::UEaseAnimationComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	UActorComponent::SetComponentTickEnabled(false);
}

void UEaseAnimationComponent::BeginPlay()
{
	Super::BeginPlay();

	if (bStartOnBeginPlay)
	{
		StartAnimation();
	}
}

void UEaseAnimationComponent::TickComponent(float DeltaTime,
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
			GetOwner()->SetActorLocation(NewLocation);
		}

		if (bAnimateRotation)
		{
			FRotator NewRotator;
			NewRotator.Pitch = EaseFloat(InitialRotation.Pitch, TargetRotation.Pitch);
			NewRotator.Yaw = EaseFloat(InitialRotation.Yaw, TargetRotation.Yaw);
			NewRotator.Roll = EaseFloat(InitialRotation.Roll, TargetRotation.Roll);
			GetOwner()->SetActorRotation(NewRotator);
		}

		if (bAnimateScale)
		{
			FVector NewScale;
			NewScale.X = EaseFloat(InitialScale.X, TargetScale.X);
			NewScale.Y = EaseFloat(InitialScale.Y, TargetScale.Y);
			NewScale.Z = EaseFloat(InitialScale.Z, TargetScale.Z);
			GetOwner()->SetActorScale3D(NewScale);
		}
	}

	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

bool UEaseAnimationComponent::GetIsPlaying() const
{
	return bIsPlaying;
}

void UEaseAnimationComponent::StartAnimation()
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
	SetInitialValues();
	CalculateTargetValues();
	OnAnimationStarted.Broadcast();
}

void UEaseAnimationComponent::StopAnimation()
{
	if (!bIsPlaying)
	{
		return;
	}

	bIsPlaying = false;
	SetComponentTickEnabled(false);
	OnAnimationStopped.Broadcast();
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

FVector UEaseAnimationComponent::GetLocation() const
{
	return Location;
}

void UEaseAnimationComponent::SetLocation(const FVector& Value)
{
	Location = Value;

	if (AnimationBehavior == EEaseAnimBehavior::Normal)
	{
		TargetLocation = Location;
	}
}

FRotator UEaseAnimationComponent::GetRotation() const
{
	return Rotation;
}

void UEaseAnimationComponent::SetRotation(const FRotator& Value)
{
	Rotation = Value;

	if (AnimationBehavior == EEaseAnimBehavior::Normal)
	{
		TargetRotation = Rotation;
	}
}

FVector UEaseAnimationComponent::GetScale() const
{
	return Scale;
}

void UEaseAnimationComponent::SetScale(const FVector& Value)
{
	Scale = Value;

	if (AnimationBehavior == EEaseAnimBehavior::Normal)
	{
		TargetScale = Scale;
	}
}

float UEaseAnimationComponent::EaseFloat(const float InitialValue,
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

	switch (AnimationBehavior)
	{
	case EEaseAnimBehavior::Normal:
		bIsPlaying = false;
		SetComponentTickEnabled(false);
		break;

	case EEaseAnimBehavior::Loop:
		SetInitialValues();
		CalculateTargetValues();
		break;

	case EEaseAnimBehavior::PingPong:
		PinPongDirection *= -1;
		SetInitialValues();
		CalculateTargetValues();
		break;
	}

	OnAnimationFinished.Broadcast();

	return TargetValue;
}

void UEaseAnimationComponent::SetInitialValues()
{
	LaunchTime = GetWorld()->GetTimeSeconds();
	InitialLocation = GetOwner()->GetActorLocation();
	InitialRotation = GetOwner()->GetActorRotation();
	InitialScale = GetOwner()->GetActorScale3D();
}

void UEaseAnimationComponent::CalculateTargetValues()
{
	switch (AnimationBehavior)
	{
	case EEaseAnimBehavior::Normal:
		TargetLocation = Location;
		TargetRotation = Rotation;
		TargetScale = Scale;
		break;

	case EEaseAnimBehavior::Loop:
		TargetLocation = InitialLocation + Location;
		TargetRotation = InitialRotation + Rotation;
		TargetScale = InitialScale + Scale;
		break;

	case EEaseAnimBehavior::PingPong:
		TargetLocation = InitialLocation + Location * PinPongDirection;
		TargetRotation = InitialRotation + Rotation * PinPongDirection;
		TargetScale = InitialScale + Scale * PinPongDirection;
	}
}
