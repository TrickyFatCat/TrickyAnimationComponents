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
	UFUNCTION(BlueprintPure, Category="TrickyEasing", DisplayName="EaseInSine")
	static double EaseInSine(const double Alpha = 0.f);
	
	UFUNCTION(BlueprintPure, Category="TrickyEasing", DisplayName="EaseOutSine")
	static double EaseOutSine(const double Alpha = 0.f);
	
	UFUNCTION(BlueprintPure, Category="TrickyEasing", DisplayName="EaseInOutSine")
	static double EaseInOutSine(const double Alpha = 0.f);
	
	UFUNCTION(BlueprintPure, Category="TrickyEasing", DisplayName="EaseInCubic")
	static double EaseInCubic(const double Alpha = 0.f);
	
	UFUNCTION(BlueprintPure, Category="TrickyEasing", DisplayName="EaseOutCubic")
	static double EaseOutCubic(const double Alpha = 0.f);
	
	UFUNCTION(BlueprintPure, Category="TrickyEasing", DisplayName="EaseInOutCubic")
	static double EaseInOutCubic(const double Alpha = 0.f);
};
