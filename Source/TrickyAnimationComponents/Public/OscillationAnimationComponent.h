// MIT License Copyright (c) 2022 Artyom "Tricky Fat Cat" Volkov

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "OscillationAnimationComponent.generated.h"



/**
 * A simple scene component which creates a floating animation.
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TRICKYANIMATIONCOMPONENTS_API UOscillationAnimationComponent : public USceneComponent
{
	GENERATED_BODY()

public:
	UOscillationAnimationComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime,
	                           ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category="TrickyAnimations|FloatingAnimaton")
	void SetIsFloating(const bool bX, const bool bY, const bool bZ);

	/**
	 * Determines the animation speed. 
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Animation")
	FVector Frequency{FVector::UpVector};

	/**
	 * Determines the position offset.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Animation")
	FVector Amplitude{FVector::UpVector};

protected:
	/**
	 * Toggles floating along the X axis.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Animation")
	bool bFloatX = false;

	/**
	 * Toggles floating along the Y axis.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Animation")
	bool bFloatY = false;

	/**
	 * Toggles floating along the Z axis.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Animation")
	bool bFloatZ = true;
	
private:
	FVector InitialLocation{FVector::ZeroVector};

	void Float(const bool bAxisAnimated,
	             float& Value,
	             const float& InitialValue,
	             const float& AxisAmplitude,
	             const float& AxisFrequency) const;

	void ToggleTick();
};
