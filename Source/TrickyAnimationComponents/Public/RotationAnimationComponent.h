// MIT License Copyright (c) Artyom "Tricky Fat Cat" Volkov

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "RotationAnimationComponent.generated.h"

/**
 * A simple scene components which rotates along chosen axis.
 */

UCLASS(ClassGroup=(TrickyAnimationComponents), meta=(BlueprintSpawnableComponent))
class TRICKYANIMATIONCOMPONENTS_API URotationAnimationComponent : public USceneComponent
{
	GENERATED_BODY()

public:
	URotationAnimationComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime,
	                           ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintGetter)
	FRotator GetRotationSpeed() const;

	UFUNCTION(BlueprintSetter)
	void SetRotationSpeed(const FRotator Value);

	UFUNCTION(BlueprintCallable, Category="TrickyAnimators|RotationAnimator")
	void SetIsRotating(const bool bX, const bool bY, const bool bZ);

protected:
	/**
	 * Toggles rotation along the X axis.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Rotation)
	bool bRotateX = false;

	/**
	 * Toggles rotation along the Y axis.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Rotation)
	bool bRotateY = false;

	/**
	 * Toggles rotation along the Z axis.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Rotation)
	bool bRotateZ = true;

	/**
	 * Determines the rotation speed along each axis.
	 */
	UPROPERTY(EditAnywhere, BlueprintGetter=GetRotationSpeed, BlueprintSetter=SetRotationSpeed, Category=Rotation)
	FRotator RotationSpeed{0.f, 1.f, 0.f};

protected:
	UPROPERTY()
	FRotator DeltaRotator{FRotator::ZeroRotator};

private:
	void ToggleTick();
};
