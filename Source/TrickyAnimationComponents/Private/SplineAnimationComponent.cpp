// MIT License Copyright (c) 2022 Artyom "Tricky Fat Cat" Volkov


#include "SplineAnimationComponent.h"

USplineAnimationComponent::USplineAnimationComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void USplineAnimationComponent::BeginPlay()
{
	Super::BeginPlay();
}


void USplineAnimationComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

