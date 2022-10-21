// MIT License Copyright (c) 2022 Artyom "Tricky Fat Cat" Volkov


#include "OscillationAnimationComponent.h"
#include "Engine/World.h"

UOscillationAnimationComponent::UOscillationAnimationComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UOscillationAnimationComponent::BeginPlay()
{
	Super::BeginPlay();

	InitialLocation = GetRelativeLocation();
	InitialRotation = GetRelativeRotation();
	InitialScale = GetRelativeScale3D();
	SetIsEnabled(bIsEnabled);
}


void UOscillationAnimationComponent::TickComponent(float DeltaTime,
                                                   ELevelTick TickType,
                                                   FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (GetWorld())
	{
		NewLocation = GetRelativeLocation();
		OscillateVector(NewLocation, InitialLocation, LocationAnimationSettings);
		SetRelativeLocation(NewLocation);

		NewRotation = GetRelativeRotation();
		OscillateRotator(NewRotation, InitialRotation, RotationAnimationSettings);
		SetRelativeRotation(NewRotation);

		NewScale = GetRelativeScale3D();
		OscillateVector(NewScale, InitialScale, ScaleAnimationSettings);
		SetRelativeScale3D(NewScale);
	}
}

bool UOscillationAnimationComponent::GetIsEnabled() const
{
	return bIsEnabled;
}

void UOscillationAnimationComponent::SetIsEnabled(const bool Value)
{
	bIsEnabled = Value;
	SetComponentTickEnabled(bIsEnabled);
}

void UOscillationAnimationComponent::OscillateAxis(float& Value,
                                                   const float& InitialValue,
                                                   const float& Amplitude,
                                                   const float& Frequency) const
{
	const float Time = GetWorld()->GetTimeSeconds();
	Value = InitialValue + Amplitude * FMath::Sin(Frequency * Time);
}

void UOscillationAnimationComponent::OscillateVector(FVector& Vector,
                                                     const FVector& InitialVector,
                                                     const FOscillationSettings& Settings) const
{
	if (Settings.bAnimateX)
	{
		OscillateAxis(Vector.X, InitialVector.X, Settings.Amplitude.X, Settings.Frequency.X);
	}

	if (Settings.bAnimateY)
	{
		OscillateAxis(Vector.Y, InitialVector.Y, Settings.Amplitude.Y, Settings.Frequency.Y);
	}

	if (Settings.bAnimateZ)
	{
		OscillateAxis(Vector.Z, InitialVector.Z, Settings.Amplitude.Z, Settings.Frequency.Z);
	}
}

void UOscillationAnimationComponent::OscillateRotator(FRotator& Rotator,
                                                      const FRotator& InitialRotator,
                                                      const FOscillationSettings& Settings) const
{
	if (Settings.bAnimateX)
	{
		OscillateAxis(Rotator.Roll, InitialRotator.Roll, Settings.Amplitude.X, Settings.Frequency.X);
	}

	if (Settings.bAnimateY)
	{
		OscillateAxis(Rotator.Pitch, InitialRotator.Pitch, Settings.Amplitude.Y, Settings.Frequency.Y);
	}

	if (Settings.bAnimateZ)
	{
		OscillateAxis(Rotator.Yaw, InitialRotator.Yaw, Settings.Amplitude.Z, Settings.Frequency.Z);
	}
}
