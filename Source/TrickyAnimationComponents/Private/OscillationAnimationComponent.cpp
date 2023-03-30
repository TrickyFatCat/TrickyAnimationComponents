// MIT License Copyright (c) Artyom "Tricky Fat Cat" Volkov


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

float UOscillationAnimationComponent::OscillateAxis(const float InitialValue,
                                                    const float Amplitude,
                                                    const float Frequency) const
{
	const float Time = GetWorld()->GetTimeSeconds();
	return InitialValue + Amplitude * FMath::Sin(Frequency * Time);
}

void UOscillationAnimationComponent::OscillateVector(FVector& Vector,
                                                     const FVector& InitialVector,
                                                     const FOscillationSettings& Settings) const
{
	if (Settings.bAnimateX)
	{
		Vector.X = OscillateAxis(InitialVector.X, Settings.Amplitude.X, Settings.Frequency.X);
	}

	if (Settings.bAnimateY)
	{
		Vector.Y = OscillateAxis(InitialVector.Y, Settings.Amplitude.Y, Settings.Frequency.Y);
	}

	if (Settings.bAnimateZ)
	{
		Vector.Z = OscillateAxis(InitialVector.Z, Settings.Amplitude.Z, Settings.Frequency.Z);
	}
}

void UOscillationAnimationComponent::OscillateRotator(FRotator& Rotator,
                                                      const FRotator& InitialRotator,
                                                      const FOscillationSettings& Settings) const
{
	if (Settings.bAnimateX)
	{
		Rotator.Roll = OscillateAxis(InitialRotator.Roll, Settings.Amplitude.X, Settings.Frequency.X);
	}

	if (Settings.bAnimateY)
	{
		Rotator.Pitch = OscillateAxis(InitialRotator.Pitch, Settings.Amplitude.Y, Settings.Frequency.Y);
	}

	if (Settings.bAnimateZ)
	{
		Rotator.Yaw = OscillateAxis(InitialRotator.Yaw, Settings.Amplitude.Z, Settings.Frequency.Z);
	}
}
