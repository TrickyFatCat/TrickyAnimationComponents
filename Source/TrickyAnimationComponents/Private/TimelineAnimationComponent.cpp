// MIT License Copyright (c) 2022 Artyom "Tricky Fat Cat" Volkov


#include "TimelineAnimationComponent.h"


UTimelineAnimationComponent::UTimelineAnimationComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


void UTimelineAnimationComponent::BeginPlay()
{
	Super::BeginPlay();
}


void UTimelineAnimationComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                                FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

