// MIT License Copyright. Created by Artyom "Tricky Fat Cat" Volkov

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "TrickyEasingLibrary.generated.h"

UENUM(BlueprintType)
enum class EEaseFunction : uint8
{
	Linear,
	InSine,
	OutSine,
	InOutSine,
	InQuad,
	OutQuad,
	InOutQuad,
	InCubic,
	OutCubic,
	InOutCubic,
	InQuart,
	OutQuart,
	InOutQuart,
	InQuint,
	OutQuint,
	InOutQuint,
	InCirc,
	OutCirc,
	InOutCirc,
	InExpo,
	OutExpo,
	InOutExpo,
	InBack,
	OutBack,
	InOutBack,
	InElastic,
	OutElastic,
	InOutElastic,
	InBounce,
	OutBounce,
	InOutBounce
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
	static double Ease(const EEaseFunction EaseFunction, const double Alpha = 0.f);

	UFUNCTION(BlueprintPure, Category="TrickyEasing")
	static double EaseFloat(double A, double B, const EEaseFunction EaseFunction, const double Alpha = 0.f);

	UFUNCTION(BlueprintPure, Category="TrickyEasing", meta=(AutoCreateRefTerm="A, B"))
	static FVector EaseVector(UPARAM(ref) FVector& A,
	                          UPARAM(ref) FVector& B,
	                          const EEaseFunction EaseFunction,
	                          const double Alpha = 0.f);

	UFUNCTION(BlueprintPure, Category="TrickyEasing", meta=(AutoCreateRefTerm="A, B"))
	static FRotator EaseRotator(UPARAM(ref) FRotator& A,
	                            UPARAM(ref) FRotator& B,
	                            const EEaseFunction EaseFunction,
	                            const double Alpha = 0.f);

	UFUNCTION(BlueprintPure, Category="TrickyEasing", DisplayName="EaseInSine")
	static double EaseInSine(const double Alpha = 0.f);

	UFUNCTION(BlueprintPure, Category="TrickyEasing", DisplayName="EaseOutSine")
	static double EaseOutSine(const double Alpha = 0.f);

	UFUNCTION(BlueprintPure, Category="TrickyEasing", DisplayName="EaseInOutSine")
	static double EaseInOutSine(const double Alpha = 0.f);

	UFUNCTION(BlueprintPure, Category="TrickyEasing", DisplayName="EaseInQuad")
	static double EaseInQuad(const double Alpha = 0.f);

	UFUNCTION(BlueprintPure, Category="TrickyEasing", DisplayName="EaseOutQuad")
	static double EaseOutQuad(const double Alpha = 0.f);

	UFUNCTION(BlueprintPure, Category="TrickyEasing", DisplayName="EaseInOutQuad")
	static double EaseInOutQuad(const double Alpha = 0.f);

	UFUNCTION(BlueprintPure, Category="TrickyEasing", DisplayName="EaseInCubic")
	static double EaseInCubic(const double Alpha = 0.f);

	UFUNCTION(BlueprintPure, Category="TrickyEasing", DisplayName="EaseOutCubic")
	static double EaseOutCubic(const double Alpha = 0.f);

	UFUNCTION(BlueprintPure, Category="TrickyEasing", DisplayName="EaseInOutCubic")
	static double EaseInOutCubic(const double Alpha = 0.f);

	UFUNCTION(BlueprintPure, Category="TrickyEasing", DisplayName="EaseInQuart")
	static double EaseInQuart(const double Alpha = 0.f);

	UFUNCTION(BlueprintPure, Category="TrickyEasing", DisplayName="EaseOutQuart")
	static double EaseOutQuart(const double Alpha = 0.f);

	UFUNCTION(BlueprintPure, Category="TrickyEasing", DisplayName="EaseInOutQuart")
	static double EaseInOutQuart(const double Alpha = 0.f);

	UFUNCTION(BlueprintPure, Category="TrickyEasing", DisplayName="EaseInQuint")
	static double EaseInQuint(const double Alpha = 0.f);

	UFUNCTION(BlueprintPure, Category="TrickyEasing", DisplayName="EaseOutQuint")
	static double EaseOutQuint(const double Alpha = 0.f);

	UFUNCTION(BlueprintPure, Category="TrickyEasing", DisplayName="EaseInOutQuint")
	static double EaseInOutQuint(const double Alpha = 0.f);

	UFUNCTION(BlueprintPure, Category="TrickyEasing", DisplayName="EaseInCirc")
	static double EaseInCirc(const double Alpha = 0.f);

	UFUNCTION(BlueprintPure, Category="TrickyEasing", DisplayName="EaseOutCirc")
	static double EaseOutCirc(const double Alpha = 0.f);

	UFUNCTION(BlueprintPure, Category="TrickyEasing", DisplayName="EaseInOutCirc")
	static double EaseInOutCirc(const double Alpha = 0.f);

	UFUNCTION(BlueprintPure, Category="TrickyEasing", DisplayName="EaseInExpo")
	static double EaseInExpo(const double Alpha = 0.f);

	UFUNCTION(BlueprintPure, Category="TrickyEasing", DisplayName="EaseOutExpo")
	static double EaseOutExpo(const double Alpha = 0.f);

	UFUNCTION(BlueprintPure, Category="TrickyEasing", DisplayName="EaseInOutExpo")
	static double EaseInOutExpo(const double Alpha = 0.f);

	UFUNCTION(BlueprintPure, Category="TrickyEasing", DisplayName="EaseInBack")
	static double EaseInBack(const double Alpha = 0.f);

	UFUNCTION(BlueprintPure, Category="TrickyEasing", DisplayName="EaseOutBack")
	static double EaseOutBack(const double Alpha = 0.f);

	UFUNCTION(BlueprintPure, Category="TrickyEasing", DisplayName="EaseInOutBack")
	static double EaseInOutBack(const double Alpha = 0.f);

	UFUNCTION(BlueprintPure, Category="TrickyEasing", DisplayName="EaseInElastic")
	static double EaseInElastic(const double Alpha = 0.f);

	UFUNCTION(BlueprintPure, Category="TrickyEasing", DisplayName="EaseOutElastic")
	static double EaseOutElastic(const double Alpha = 0.f);

	UFUNCTION(BlueprintPure, Category="TrickyEasing", DisplayName="EaseInOutElastic")
	static double EaseInOutElastic(const double Alpha = 0.f);

	UFUNCTION(BlueprintPure, Category="TrickyEasing", DisplayName="EaseInBounce")
	static double EaseInBounce(const double Alpha = 0.f);

	UFUNCTION(BlueprintPure, Category="TrickyEasing", DisplayName="EaseOutBounce")
	static double EaseOutBounce(const double Alpha = 0.f);

	UFUNCTION(BlueprintPure, Category="TrickyEasing", DisplayName="EaseInOutBounce")
	static double EaseInOutBounce(const double Alpha = 0.f);
};
