// MIT License Copyright (c) 2022 Artyom "Tricky Fat Cat" Volkov


#include "FloatingAnimationComponent.h"
#include "Engine/World.h"

UFloatingAnimationComponent::UFloatingAnimationComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UFloatingAnimationComponent::BeginPlay()
{
	Super::BeginPlay();

	InitialLocation = GetRelativeLocation();
	ToggleTick();
}


void UFloatingAnimationComponent::TickComponent(float DeltaTime,
                                                ELevelTick TickType,
                                                FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (GetWorld())
	{
		FVector CurrentLocation = GetRelativeLocation();

		Float(bFloatX, CurrentLocation.X, InitialLocation.X, Amplitude.X, Frequency.X);
		Float(bFloatY, CurrentLocation.Y, InitialLocation.Y, Amplitude.Y, Frequency.Y);
		Float(bFloatZ, CurrentLocation.Z, InitialLocation.Z, Amplitude.Z, Frequency.Z);

		SetRelativeLocation(CurrentLocation);
	}
}

void UFloatingAnimationComponent::SetIsFloating(const bool bX, const bool bY, const bool bZ)
{
	bFloatX = bX;
	bFloatY = bY;
	bFloatZ = bZ;

	ToggleTick();
}

void UFloatingAnimationComponent::Float(const bool bAxisAnimated,
                                          float& Value,
                                          const float& InitialValue,
                                          const float& AxisAmplitude,
                                          const float& AxisFrequency) const
{
	if (bAxisAnimated)
	{
		const float Time = GetWorld()->GetTimeSeconds();
		Value = InitialValue + AxisAmplitude * FMath::Sin(AxisFrequency * Time);
	}
}

void UFloatingAnimationComponent::ToggleTick()
{
	SetComponentTickEnabled((!bFloatX && !bFloatY && !bFloatZ) || (bFloatX || bFloatY || bFloatZ));
}
