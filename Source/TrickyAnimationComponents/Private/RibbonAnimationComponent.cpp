// MIT License Copyright (c) 2022 Artyom "Tricky Fat Cat" Volkov


#include "RibbonAnimationComponent.h"

URibbonAnimationComponent::URibbonAnimationComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void URibbonAnimationComponent::BeginPlay()
{
	Super::BeginPlay();
}


void URibbonAnimationComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (TargetActor && bIsEnabled)
	{
		const FVector CurrentLocation = GetOwner()->GetActorLocation();
		const FVector TargetLocation = TargetActor->GetActorLocation() + LocationOffset;
		const FVector NewLocation = FMath::InterpEaseInOut(CurrentLocation, TargetLocation, RibbonPower, 1.f);
		GetOwner()->SetActorLocation(NewLocation);
	}
}

