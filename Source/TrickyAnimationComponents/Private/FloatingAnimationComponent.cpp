// MIT License Copyright (c) 2022 Artyom "Tricky Fat Cat" Volkov


#include "FloatingAnimationComponent.h"

UFloatingAnimationComponent::UFloatingAnimationComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UFloatingAnimationComponent::BeginPlay()
{
	Super::BeginPlay();

	InitialLocation = GetRelativeLocation();
}


void UFloatingAnimationComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                                FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);;

	if (GetWorld())
	{
		const float Time = GetWorld()->GetTimeSeconds();
		FVector CurrentLocation = GetRelativeLocation();

		auto Animate = [&](const bool bIsAnimated,
		                   float& Value,
		                   const float& InitialValue,
		                   const float& Amplitude,
		                   const float& Frequency)
		{
			if (bIsAnimated)
			{
				Value = InitialValue + Amplitude * FMath::Sin(Frequency * Time);
			}
		};
		
		Animate(bAnimateX, CurrentLocation.X, InitialLocation.X, Amplitude.X, Frequency.X);
		Animate(bAnimateY, CurrentLocation.Y, InitialLocation.Y, Amplitude.Y, Frequency.Y);
		Animate(bAnimateZ, CurrentLocation.Z, InitialLocation.Z, Amplitude.Z, Frequency.Z);
		
		SetRelativeLocation(CurrentLocation);
	}
}

void UFloatingAnimationComponent::SetIsAnimated(const bool bX, const bool bY, const bool bZ)
{
	bAnimateX = bX;
	bAnimateY = bY;
	bAnimateZ = bZ;
}
