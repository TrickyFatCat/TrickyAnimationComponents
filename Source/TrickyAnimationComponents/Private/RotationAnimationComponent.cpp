// MIT License. Copyright (c) 2022 Artyom "Tricky Fat Cat" Volkov


#include "RotationAnimationComponent.h"

URotationAnimationComponent::URotationAnimationComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void URotationAnimationComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                                FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	bRotateX ? DeltaRotator.Roll = DeltaRotationX : DeltaRotator.Roll = 0.f;
	bRotateY ? DeltaRotator.Pitch = DeltaRotationY : DeltaRotator.Pitch = 0.f;
	bRotateZ ? DeltaRotator.Yaw = DeltaRotationZ : DeltaRotator.Yaw = 0.f;

	if (DeltaRotator.Equals(FRotator::ZeroRotator))
	{
		AddLocalRotation(DeltaRotator);
	}
}
