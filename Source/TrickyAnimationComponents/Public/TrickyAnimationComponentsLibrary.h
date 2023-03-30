// MIT License Copyright (c) Artyom "Tricky Fat Cat" Volkov

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "TrickyAnimationComponentsLibrary.generated.h"

UENUM(BlueprintType)
enum class EEaseAnimBehavior : uint8
{
	Normal,
	Loop,
	AdditiveLoop,
	PingPong
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAnimationFinishedSignature);

/**
 * 
 */
UCLASS()
class TRICKYANIMATIONCOMPONENTS_API UTrickyAnimationComponentsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	template <typename T>
	static void SwapValues(T& A, T& B)
	{
		const T C = A;
		A = B;
		B = C;
	}

	static void EaseVector(FVector& Value,
	                       const FVector& InitialValue,
	                       const FVector& TargetValue,
	                       const float Alpha,
	                       const TEnumAsByte<EEasingFunc::Type> EaseFunction,
	                       const float BlendExp,
	                       const int32 Steps);

	static void EaseRotator(FRotator& Value,
	                        const FRotator& InitialValue,
	                        const FRotator& TargetValue,
	                        const float Alpha,
	                        const TEnumAsByte<EEasingFunc::Type> EaseFunction,
	                        const float BlendExp,
	                        const int32 Steps);
};
