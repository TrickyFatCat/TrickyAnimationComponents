// MIT License. Copyright (c) 2022 Artyom "Tricky Fat Cat" Volkov


#include "RotationAnimationComponent.h"

URotationAnimationComponent::URotationAnimationComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void URotationAnimationComponent::BeginPlay()
{
	Super::BeginPlay();

	DeltaRotator = RotationSpeed;
}

void URotationAnimationComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                                FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bRotateX || bRotateY || bRotateZ)
	{
		AddLocalRotation(DeltaRotator);
	}
}

FRotator URotationAnimationComponent::GetRotationSpeed() const
{
	return RotationSpeed;
}

void URotationAnimationComponent::SetRotationSpeed(const FRotator Value)
{
	RotationSpeed = Value;
	DeltaRotator = Value;
}

void URotationAnimationComponent::SetIsRotating(const bool bX, const bool bY, const bool bZ)
{
	bRotateX = bX;
	bRotateY = bY;
	bRotateZ = bZ;
}
