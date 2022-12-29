// MIT License Copyright (c) 2022 Artyom "Tricky Fat Cat" Volkov


#include "FollowAnimationComponent.h"
#include "GameFramework/Actor.h"

UFollowAnimationComponent::UFollowAnimationComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


bool UFollowAnimationComponent::GetIsEnabled() const
{
	return bIsEnabled;
}

void UFollowAnimationComponent::SetIsEnabled(const bool Value)
{
	bIsEnabled = Value;
	SetComponentTickEnabled(bIsEnabled);
}

void UFollowAnimationComponent::BeginPlay()
{
	Super::BeginPlay();
	SetComponentTickEnabled(bIsEnabled);
}


void UFollowAnimationComponent::TickComponent(float DeltaTime,
                                              ELevelTick TickType,
                                              FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (TargetActor || !bFollowActor)
	{
		CurrentLocation = GetOwner()->GetActorLocation();
		TargetLocation = bFollowActor ? TargetActor->GetActorLocation() : Location;
		TargetLocation += TargetLocationOffset;
		NewLocation = FMath::VInterpTo(CurrentLocation, TargetLocation, DeltaTime, Speed);
		GetOwner()->SetActorLocation(NewLocation);
	}
}