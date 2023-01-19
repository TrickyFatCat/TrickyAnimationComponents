// MIT License Copyright. Created by Artyom "Tricky Fat Cat" Volkov

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "TrickyAnimationComponentsLibrary.generated.h"

UENUM(BlueprintType)
enum class EEaseAnimBehavior : uint8
{
	Normal,
	Additive,
	PingPong
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAnimationStartedSignature);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAnimationStoppedSignature);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAnimationFinishedSignature);

/**
 * 
 */
UCLASS()
class TRICKYANIMATIONCOMPONENTS_API UTrickyAnimationComponentsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
};
