// MIT License Copyright (c) 2022 Artyom "Tricky Fat Cat" Volkov

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "FloatingAnimationComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TRICKYANIMATIONCOMPONENTS_API UFloatingAnimationComponent : public USceneComponent
{
	GENERATED_BODY()

public:
	UFloatingAnimationComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category="TrickyAnimations|FloatingAnimaton")
	void SetIsAnimated(const bool bX, const bool bY, const bool bZ);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Animation")
	FVector Frequency{FVector::UpVector};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Animation")
	FVector Amplitude{FVector::UpVector};
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Animation")
	bool bAnimateX = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Animation")
	bool bAnimateY = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Animation")
	bool bAnimateZ = true;
private:
	FVector InitialLocation{FVector::ZeroVector};
};
