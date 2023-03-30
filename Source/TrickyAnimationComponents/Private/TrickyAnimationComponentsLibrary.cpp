// MIT License Copyright (c) Artyom "Tricky Fat Cat" Volkov

#include "TrickyAnimationComponentsLibrary.h"
#include "Kismet/KismetMathLibrary.h"


void UTrickyAnimationComponentsLibrary::EaseVector(FVector& Value,
                                                   const FVector& InitialValue,
                                                   const FVector& TargetValue,
                                                   const float Alpha,
                                                   const TEnumAsByte<EEasingFunc::Type> EaseFunction,
                                                   const float BlendExp,
                                                   const int32 Steps)
{
	Value.X = UKismetMathLibrary::Ease(InitialValue.X, TargetValue.X, Alpha, EaseFunction, BlendExp, Steps);
	Value.Y = UKismetMathLibrary::Ease(InitialValue.Y, TargetValue.Y, Alpha, EaseFunction, BlendExp, Steps);
	Value.Z = UKismetMathLibrary::Ease(InitialValue.Z, TargetValue.Z, Alpha, EaseFunction, BlendExp, Steps);
}

void UTrickyAnimationComponentsLibrary::EaseRotator(FRotator& Value,
                                                    const FRotator& InitialValue,
                                                    const FRotator& TargetValue,
                                                    const float Alpha,
                                                    const TEnumAsByte<EEasingFunc::Type> EaseFunction,
                                                    const float BlendExp,
                                                    const int32 Steps)
{
	Value.Pitch = UKismetMathLibrary::Ease(InitialValue.Pitch, TargetValue.Pitch, Alpha, EaseFunction, BlendExp, Steps);
	Value.Yaw = UKismetMathLibrary::Ease(InitialValue.Yaw, TargetValue.Yaw, Alpha, EaseFunction, BlendExp, Steps);
	Value.Roll = UKismetMathLibrary::Ease(InitialValue.Roll, TargetValue.Roll, Alpha, EaseFunction, BlendExp, Steps);
}
