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
	float RibbonPower = 0.15f;

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
