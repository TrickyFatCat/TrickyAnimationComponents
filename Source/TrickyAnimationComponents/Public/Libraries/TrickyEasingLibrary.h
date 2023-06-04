// MIT License Copyright. Created by Artyom "Tricky Fat Cat" Volkov

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "TrickyEasingLibrary.generated.h"

UENUM()
enum class EEaseType : uint8
{
	Linear,
	InSine,
	OutSine,
	InOutSine,
	InCubic,
	OutCubic,
	InOutCubic,
	InQuint,
	OutQuint,
	InOutQuint
};
/**
 * 
 */
UCLASS()
class TRICKYANIMATIONCOMPONENTS_API UTrickyEasingLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category="TrickyEasing")
	static double Ease(const EEaseType EaseType, const double Alpha = 0.f);
	
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
	
	UFUNCTION(BlueprintPure, Category="TrickyEasing", DisplayName="EaseInQuint")
	static double EaseInQuint(const double Alpha = 0.f);

	UFUNCTION(BlueprintPure, Category="TrickyEasing", DisplayName="EaseOutQuint")
	static double EaseOutQuint(const double Alpha = 0.f);
	
	UFUNCTION(BlueprintPure, Category="TrickyEasing", DisplayName="EaseInOutQuint")
	static double EaseInOutQuint(const double Alpha = 0.f);
};
