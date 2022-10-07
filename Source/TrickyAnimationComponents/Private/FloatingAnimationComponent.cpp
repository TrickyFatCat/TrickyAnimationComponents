// MIT License Copyright (c) 2022 Artyom "Tricky Fat Cat" Volkov


#include "FloatingAnimationComponent.h"

UFloatingAnimationComponent::UFloatingAnimationComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UFloatingAnimationComponent::BeginPlay()
{
	Super::BeginPlay();
}


void UFloatingAnimationComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

