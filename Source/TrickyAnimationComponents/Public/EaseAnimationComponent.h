// MIT License Copyright (c) 2022 Artyom "Tricky Fat Cat" Volkov

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "EaseAnimationComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TRICKYANIMATIONCOMPONENTS_API UEaseAnimationComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UEaseAnimationComponent();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Animation")
	bool bIsEnabled = true;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Animation")
	AActor* TargetActor = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Animation")
	FVector TargetLocationOffset{FVector::ZeroVector};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Animation")
	TEnumAsByte<EEasingFunc::Type> EasingFunction = EEasingFunc::EaseInOut;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Animation")
	float Alpha = 0.15f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Animation")
	float Exponent = 2.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Animation")
	int32 SubStep = 10.f;
	
protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

private:
	FVector CurrentLocation{FVector::ZeroVector};
	FVector TargetLocation{FVector::ZeroVector};
	FVector NewLocation{FVector::ZeroVector};
	void EaseAxis(const float& CurrentLocationAxis, const float& TargetLocationAxis, float& NewLocationAxis) const;
};
