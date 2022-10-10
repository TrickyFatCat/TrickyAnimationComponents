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


void UEaseAnimationComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (TargetActor && bIsEnabled)
	{
		const FVector CurrentLocation = GetOwner()->GetActorLocation();
		const FVector TargetLocation = TargetActor->GetActorLocation() + TargetLocationOffset;
		const FVector NewLocation = FMath::InterpEaseInOut(CurrentLocation, TargetLocation, RibbonPower, 1.f);
		GetOwner()->SetActorLocation(NewLocation);
	}
}

