// MIT License Copyright (c) 2022 Artyom "Tricky Fat Cat" Volkov

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "OscillationAnimationComponent.generated.h"


USTRUCT(BlueprintType)
struct FOscillationSettings
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="OscillationSettings")
	bool bAnimateX = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="OscillationSettings")
	bool bAnimateY = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="OscillationSettings")
	bool bAnimateZ = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="OscillationSettings")
	FVector Amplitude{FVector::ZeroVector};
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="OscillationSettings")
	FVector Frequency{FVector::ZeroVector};
};


/**
 * A simple scene component which creates a floating animation.
 */
UCLASS(ClassGroup=(TrickyAnimationComponents), meta=(BlueprintSpawnableComponent))
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Animation")
	FOscillationSettings LocationAnimationSettings{};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Animation")
	FOscillationSettings RotationAnimationSettings{};
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Animation")
	FOscillationSettings ScaleAnimationSettings{};

private:
	FVector InitialLocation{FVector::ZeroVector};
	FRotator InitialRotation{FRotator::ZeroRotator};
	FVector InitialScale{FVector::ZeroVector};
	
	FVector NewLocation{FVector::ZeroVector};
	FRotator NewRotation{FRotator::ZeroRotator};
	FVector NewScale{FVector::ZeroVector};
	
	void OscillateAxis(float& Value,
	                   const float& InitialValue,
	                   const float& Amplitude,
	                   const float& Frequency) const;

	void OscillateVector(FVector& Vector, const FVector& InitialVector, const FOscillationSettings& Settings) const;

	void OscillateRotator(FRotator& Rotator,
	                      const FRotator& InitialRotator,
	                      const FOscillationSettings& Settings) const;
};
