// MIT License Copyright (c) 2022 Artyom "Tricky Fat Cat" Volkov


#include "EaseAnimationComponent.h"

UEaseAnimationComponent::UEaseAnimationComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UEaseAnimationComponent::BeginPlay()
{
	Super::BeginPlay();
}


void UEaseAnimationComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                            FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (TargetActor && bIsEnabled)
	{
		CurrentLocation = GetOwner()->GetActorLocation();
		TargetLocation = TargetActor->GetActorLocation() + TargetLocationOffset;
		EaseAxis(CurrentLocation.X, TargetLocation.X, NewLocation.X);
		EaseAxis(CurrentLocation.Y, TargetLocation.Y, NewLocation.Y);
		EaseAxis(CurrentLocation.Z, TargetLocation.Z, NewLocation.Z);
		GetOwner()->SetActorLocation(NewLocation);
	}
}

void UEaseAnimationComponent::EaseAxis(const float& CurrentLocationAxis, const float& TargetLocationAxis,
                                       float& NewLocationAxis) const
{
	NewLocationAxis = UKismetMathLibrary::Ease(CurrentLocationAxis,TargetLocationAxis, Alpha, EasingFunction, Exponent,
	                                           SubStep);
}
