// MIT License. Copyright (c) 2022 Artyom "Tricky Fat Cat" Volkov

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RotationAnimationComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TRICKYANIMATIONCOMPONENTS_API URotationAnimationComponent : public USceneComponent
{
	GENERATED_BODY()

public:
	URotationAnimationComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Rotation)
	bool bRotateX = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Rotation, meta=(EditCondition="bRotateX"))
	float DeltaRotationX = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Rotation)
	bool bRotateY = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Rotation, meta=(EditCondition="bRotateY"))
	float DeltaRotationY = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Rotation)
	bool bRotateZ = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Rotation, meta=(EditCondition="bRotateZ"))
	float DeltaRotationZ = 1.f;

protected:
	UPROPERTY()
	FRotator DeltaRotator{FRotator::ZeroRotator};
};
