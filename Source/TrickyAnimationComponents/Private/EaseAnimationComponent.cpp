// MIT License Copyright (c) 2022 Artyom "Tricky Fat Cat" Volkov


#include "EaseAnimationComponent.h"
#include "GameFramework/Actor.h"

UEaseAnimationComponent::UEaseAnimationComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


bool UEaseAnimationComponent::GetIsEnabled() const
{
	return bIsEnabled;
}

void UEaseAnimationComponent::SetIsEnabled(const bool Value)
{
	bIsEnabled = Value;
	SetComponentTickEnabled(bIsEnabled);
}

void UEaseAnimationComponent::BeginPlay()
{
	Super::BeginPlay();
	SetComponentTickEnabled(bIsEnabled);
}


void UEaseAnimationComponent::TickComponent(float DeltaTime,
                                            ELevelTick TickType,
                                            FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (TargetActor || !bFollowActor)
	{
		CurrentLocation = GetOwner()->GetActorLocation();
		TargetLocation = bFollowActor ? TargetActor->GetActorLocation() : SpecificLocation;
		TargetLocation += LocationOffset;
		NewLocation.X = EaseAxis(CurrentLocation.X, TargetLocation.X);
		NewLocation.Y = EaseAxis(CurrentLocation.Y, TargetLocation.Y);
		NewLocation.Z = EaseAxis(CurrentLocation.Z, TargetLocation.Z);
		GetOwner()->SetActorLocation(NewLocation);
	}
}

float UEaseAnimationComponent::EaseAxis(const float CurrentLocationAxis,
                                        const float TargetLocationAxis) const
{
	return UKismetMathLibrary::Ease(CurrentLocationAxis,
	                                TargetLocationAxis,
	                                Alpha,
	                                EasingFunction,
	                                Exponent,
	                                SubStep);
}
