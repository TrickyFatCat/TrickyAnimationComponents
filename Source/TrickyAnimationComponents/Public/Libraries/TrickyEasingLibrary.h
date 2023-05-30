// MIT License Copyright. Created by Artyom "Tricky Fat Cat" Volkov

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "TrickyEasingLibrary.generated.h"

/**
 * 
 */
UCLASS()
class TRICKYANIMATIONCOMPONENTS_API UTrickyEasingLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category="TrickyEasing")
	static double EaseInSine(const double Alpha = 0.f);
	
	UFUNCTION(BlueprintPure, Category="TrickyEasing")
	static double EaseOutSine(const double Alpha = 0.f);
	
	UFUNCTION(BlueprintPure, Category="TrickyEasing")
	static double EaseInOutSine(const double Alpha = 0.f);
};
