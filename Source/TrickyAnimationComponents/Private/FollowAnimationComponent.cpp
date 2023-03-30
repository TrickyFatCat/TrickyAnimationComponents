// MIT License Copyright (c) Artyom "Tricky Fat Cat" Volkov

#include "FollowAnimationComponent.h"
#include "GameFramework/Actor.h"

UFollowAnimationComponent::UFollowAnimationComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	UActorComponent::SetComponentTickEnabled(false);
}


bool UFollowAnimationComponent::StartFollowing()
{
	if (bIsFollowing)
	{
		return false;
	}
	
	bIsFollowing = true;
	SetComponentTickEnabled(true);
	return true;
}

bool UFollowAnimationComponent::StopFollowing()
{
	if (!bIsFollowing)
	{
		return false;
	}
	
	bIsFollowing = false;
	SetComponentTickEnabled(false);
	return true;
}

bool UFollowAnimationComponent::GetIsFollowing() const
{
	return bIsFollowing;
}

void UFollowAnimationComponent::BeginPlay()
{
	Super::BeginPlay();
	SetComponentTickEnabled(bIsFollowing);
}


void UFollowAnimationComponent::TickComponent(float DeltaTime,
                                              ELevelTick TickType,
                                              FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bIsFollowing && (TargetActor || !bFollowActor))
	{
		CurrentLocation = GetOwner()->GetActorLocation();
		TargetLocation = bFollowActor ? TargetActor->GetActorLocation() : Location;
		TargetLocation += TargetLocationOffset;
		NewLocation = FMath::VInterpTo(CurrentLocation, TargetLocation, DeltaTime, Speed);
		GetOwner()->SetActorLocation(NewLocation);
	}
}