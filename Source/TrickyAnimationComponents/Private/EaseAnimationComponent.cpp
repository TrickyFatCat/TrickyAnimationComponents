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
		Start();
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

void UEaseAnimationComponent::Start()
{
	if (bIsPlaying)
	{
		return;
	}

	if (Duration <= 0.f)
	{
		UE_LOG(LogTemp, Error, TEXT("Ease animation duration is <= 0."));
		return;
	}

	LaunchTime = GetWorld()->GetTimeSeconds();
	InitialLocation = GetOwner()->GetActorLocation();
	InitialRotation = GetOwner()->GetActorRotation();
	InitialScale = GetOwner()->GetActorScale3D();	

	bIsPlaying = true;
	SetComponentTickEnabled(true);
	OnAnimationStarted.Broadcast();
}

void UEaseAnimationComponent::Stop()
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

	OnAnimationFinished.Broadcast();

	if (bIsLooping)
	{
		LaunchTime = GetWorld()->GetTimeSeconds();
		
		switch(AnimationBehavior)
		{
		case EEaseAnimBehavior::Normal:
			GetOwner()->SetActorLocation(InitialLocation);
			GetOwner()->SetActorRotation(InitialRotation);
			GetOwner()->SetActorScale3D(InitialScale);
			break;

		case EEaseAnimBehavior::PingPong:
			UTrickyAnimationComponentsLibrary::SwapValues<FVector>(InitialLocation, TargetLocation);
			UTrickyAnimationComponentsLibrary::SwapValues<FRotator>(InitialRotation, TargetRotation);
			UTrickyAnimationComponentsLibrary::SwapValues<FVector>(InitialScale, TargetScale);
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
