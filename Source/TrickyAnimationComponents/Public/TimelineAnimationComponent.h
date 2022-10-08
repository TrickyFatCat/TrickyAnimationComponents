// MIT License Copyright (c) 2022 Artyom "Tricky Fat Cat" Volkov

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TimelineAnimationComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TRICKYANIMATIONCOMPONENTS_API UTimelineAnimationComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UTimelineAnimationComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
