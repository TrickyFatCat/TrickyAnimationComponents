// MIT License Copyright (c) 2022 Artyom "Tricky Fat Cat" Volkov

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "RibbonAnimationComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TRICKYANIMATIONCOMPONENTS_API URibbonAnimationComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	URibbonAnimationComponent();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Animation")
	bool bIsEnabled = true;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Animation")
	AActor* TargetActor = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Animation")
	FVector LocationOffset{FVector::ZeroVector};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Animation")
	float RibbonPower = 0.15f;

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
