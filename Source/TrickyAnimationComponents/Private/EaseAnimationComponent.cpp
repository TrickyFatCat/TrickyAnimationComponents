// MIT License Copyright (c) 2022 Artyom "Tricky Fat Cat" Volkov


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
	SetIsEnabled(bIsEnabled);
}

void UEaseAnimationComponent::TickComponent(float DeltaTime,
                                            ELevelTick TickType,
                                            FActorComponentTickFunction* ThisTickFunction)
{
	if (bAnimateLocation)
	{
		FVector NewLocation;
		NewLocation.X = EaseFloat(InitialLocation.X, Location.X);
		NewLocation.Y = EaseFloat(InitialLocation.Y, Location.Y);
		NewLocation.Z = EaseFloat(InitialLocation.Z, Location.Z);
		GetOwner()->SetActorLocation(NewLocation);
	}

	if (bAnimateRotation)
	{
		FRotator NewRotator;
		NewRotator.Pitch = EaseFloat(InitialRotator.Pitch, Rotation.Pitch);
		NewRotator.Yaw = EaseFloat(InitialRotator.Yaw, Rotation.Yaw);
		NewRotator.Roll = EaseFloat(InitialRotator.Roll, Rotation.Roll);
		GetOwner()->SetActorRotation(NewRotator);
	}

	if (bAnimateScale)
	{
		FVector NewScale;
		NewScale.X = EaseFloat(InitialScale.X, Scale.X);
		NewScale.Y = EaseFloat(InitialScale.Y, Scale.Y);
		NewScale.Z = EaseFloat(InitialScale.Z, Scale.Z);
		GetOwner()->SetActorScale3D(NewScale);
	}

	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

bool UEaseAnimationComponent::GetIsEnabled() const
{
	return bIsEnabled;
}

void UEaseAnimationComponent::SetIsEnabled(const bool Value)
{
	if (EaseDuration <= 0.f)
	{
		UE_LOG(LogTemp, Error, TEXT("Can't start ease animation because duration is < 0"));
		EaseDuration = 1.f;
	}

	bIsEnabled = Value;
	SetComponentTickEnabled(bIsEnabled);

	if (!GetWorld() || !bIsEnabled)
	{
		return;
	}

	LaunchTime = GetWorld()->GetTimeSeconds();
	InitialLocation = GetOwner()->GetActorLocation();
	InitialRotator = GetOwner()->GetActorRotation();
	InitialScale = GetOwner()->GetActorScale3D();
}

float UEaseAnimationComponent::GetEaseDuration() const
{
	return EaseDuration;
}

void UEaseAnimationComponent::SetEaseDuration(const float Value)
{
	if (Value < 0.f)
	{
		return;
	}

	EaseDuration = Value;
}

float UEaseAnimationComponent::EaseFloat(const float InitialValue,
                                         const float Value)
{
	const float CurrentTime = GetWorld()->GetTimeSeconds();
	float TargetValue = 0;

	switch (AnimationBehavior)
	{
	case EEaseAnimBehavior::Normal:
		TargetValue = Value;
		break;

	case EEaseAnimBehavior::Loop:
		TargetValue = InitialValue + Value;
		break;

	case EEaseAnimBehavior::PingPong:
		TargetValue = InitialValue + Value * PinPongDirection;
		break;
	}

	if (CurrentTime - LaunchTime < EaseDuration)
	{
		const float Alpha = (CurrentTime - LaunchTime) / EaseDuration;
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
		SetIsEnabled(false);
		break;

	case EEaseAnimBehavior::Loop:
		SetIsEnabled(true);
		break;

	case EEaseAnimBehavior::PingPong:
		PinPongDirection *= -1;
		SetIsEnabled(true);
		break;
	}

	return TargetValue;
}
