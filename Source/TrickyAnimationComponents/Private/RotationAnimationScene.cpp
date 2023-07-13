// MIT License Copyright (c) Artyom "Tricky Fat Cat" Volkov


#include "RotationAnimationScene.h"

URotationAnimationScene::URotationAnimationScene()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void URotationAnimationScene::BeginPlay()
{
	Super::BeginPlay();

	DeltaRotator = RotationSpeed;
	ToggleTick();
}

void URotationAnimationScene::TickComponent(float DeltaTime,
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

FRotator URotationAnimationScene::GetRotationSpeed() const
{
	return RotationSpeed;
}

void URotationAnimationScene::SetRotationSpeed(const FRotator Value)
{
	RotationSpeed = Value;
	DeltaRotator = Value;
}

void URotationAnimationScene::SetIsRotating(const bool bX, const bool bY, const bool bZ)
{
	bRotateX = bX;
	bRotateY = bY;
	bRotateZ = bZ;
	ToggleTick();
}

void URotationAnimationScene::ToggleTick()
{
	SetComponentTickEnabled((!bRotateX && !bRotateY && !bRotateZ) || (bRotateX || bRotateY || bRotateZ));
}
