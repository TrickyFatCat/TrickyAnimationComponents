// MIT License Copyright (c) Artyom "Tricky Fat Cat" Volkov


#include "RotationAnimationComponent.h"

URotationAnimationComponent::URotationAnimationComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void URotationAnimationComponent::BeginPlay()
{
	Super::BeginPlay();

	DeltaRotator = RotationSpeed;
	ToggleTick();
}

void URotationAnimationComponent::TickComponent(float DeltaTime,
                                                ELevelTick TickType,
                                                FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bRotateX || bRotateY || bRotateZ)
	{
		DeltaRotator.Roll = bRotateX ? RotationSpeed.Roll : 0.f;
		DeltaRotator.Pitch = bRotateY ? RotationSpeed.Pitch : 0.f;
		DeltaRotator.Yaw = bRotateZ ? RotationSpeed.Yaw : 0.f;

		AddLocalRotation(DeltaRotator * DeltaTime);
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
	ToggleTick();
}

void URotationAnimationComponent::ToggleTick()
{
	SetComponentTickEnabled((!bRotateX && !bRotateY && !bRotateZ) || (bRotateX || bRotateY || bRotateZ));
}
