// MIT License Copyright. Created by Artyom "Tricky Fat Cat" Volkov


#include "Libraries/TrickyEasingLibrary.h"

double UTrickyEasingLibrary::Ease(const EEaseFunction EaseFunction, const double Alpha)
{
	double Result = 0.f;
	switch (EaseFunction)
	{
	case EEaseFunction::Linear:
		Result = Alpha;
		break;

	case EEaseFunction::InSine:
		Result = EaseInSine(Alpha);
		break;

	case EEaseFunction::OutSine:
		Result = EaseOutSine(Alpha);
		break;

	case EEaseFunction::InOutSine:
		Result = EaseInOutSine(Alpha);
		break;

	case EEaseFunction::InQuad:
		Result = EaseInQuad(Alpha);
		break;

	case EEaseFunction::OutQuad:
		Result = EaseOutQuad(Alpha);
		break;

	case EEaseFunction::InOutQuad:
		Result = EaseInOutQuad(Alpha);
		break;

	case EEaseFunction::InCubic:
		Result = EaseInCubic(Alpha);
		break;

	case EEaseFunction::OutCubic:
		Result = EaseOutCubic(Alpha);
		break;

	case EEaseFunction::InOutCubic:
		Result = EaseInOutCubic(Alpha);
		break;

	case EEaseFunction::InQuart:
		Result = EaseInQuart(Alpha);
		break;

	case EEaseFunction::OutQuart:
		Result = EaseOutQuart(Alpha);
		break;

	case EEaseFunction::InOutQuart:
		Result = EaseInOutQuart(Alpha);
		break;

	case EEaseFunction::InQuint:
		Result = EaseInQuint(Alpha);
		break;

	case EEaseFunction::OutQuint:
		Result = EaseOutQuint(Alpha);
		break;

	case EEaseFunction::InOutQuint:
		Result = EaseInOutQuint(Alpha);
		break;

	case EEaseFunction::InCirc:
		Result = EaseInCirc(Alpha);
		break;

	case EEaseFunction::OutCirc:
		Result = EaseOutCirc(Alpha);
		break;

	case EEaseFunction::InOutCirc:
		Result = EaseInOutCirc(Alpha);
		break;

	case EEaseFunction::InExpo:
		Result = EaseInExpo(Alpha);
		break;

	case EEaseFunction::OutExpo:
		Result = EaseOutExpo(Alpha);
		break;

	case EEaseFunction::InOutExpo:
		Result = EaseInOutExpo(Alpha);
		break;

	case EEaseFunction::InBack:
		Result = EaseInBack(Alpha);
		break;

	case EEaseFunction::OutBack:
		Result = EaseOutBack(Alpha);
		break;

	case EEaseFunction::InOutBack:
		Result = EaseInOutBack(Alpha);
		break;

	case EEaseFunction::InElastic:
		Result = EaseInElastic(Alpha);
		break;

	case EEaseFunction::OutElastic:
		Result = EaseOutElastic(Alpha);
		break;

	case EEaseFunction::InOutElastic:
		Result = EaseInOutElastic(Alpha);
		break;

	case EEaseFunction::InBounce:
		Result = EaseInBounce(Alpha);
		break;

	case EEaseFunction::OutBounce:
		Result = EaseOutBounce(Alpha);
		break;

	case EEaseFunction::InOutBounce:
		Result = EaseInOutBounce(Alpha);
		break;

	default: ;
	}

	return Result;
}

double UTrickyEasingLibrary::EaseFloat(double A, double B, const EEaseFunction EaseFunction, const double Alpha)
{
	return FMath::Lerp(A, B, Ease(EaseFunction, Alpha));
}

FVector UTrickyEasingLibrary::EaseVector(FVector& A, FVector& B, const EEaseFunction EaseFunction, const double Alpha)
{
	FVector NewVector = FVector::Zero();

	NewVector.X = FMath::Lerp(A.X, B.X, Ease(EaseFunction, Alpha));
	NewVector.Y = FMath::Lerp(A.Y, B.Y, Ease(EaseFunction, Alpha));
	NewVector.Z = FMath::Lerp(A.Z, B.Z, Ease(EaseFunction, Alpha));

	return NewVector;
}

FRotator UTrickyEasingLibrary::EaseRotator(FRotator& A,
                                           FRotator& B,
                                           const EEaseFunction EaseFunction,
                                           const double Alpha)
{
	FRotator NewRotator = FRotator(0.f);

	NewRotator.Pitch = FMath::Lerp(A.Pitch, B.Pitch, Ease(EaseFunction, Alpha));
	NewRotator.Yaw = FMath::Lerp(A.Yaw, B.Yaw, Ease(EaseFunction, Alpha));
	NewRotator.Roll = FMath::Lerp(A.Roll, B.Roll, Ease(EaseFunction, Alpha));

	return NewRotator;
}

double UTrickyEasingLibrary::EaseInSine(const double Alpha)
{
	if (Alpha <= 0.f)
	{
		return 0.f;
	}

	if (Alpha >= 1.f)
	{
		return 1.f;
	}

	return 1.f - FMath::Cos((Alpha * PI) * 0.5f);
}

double UTrickyEasingLibrary::EaseOutSine(const double Alpha)
{
	if (Alpha <= 0.f)
	{
		return 0.f;
	}

	if (Alpha >= 1.f)
	{
		return 1.f;
	}

	return FMath::Sin((Alpha * PI) * 0.5f);
}

double UTrickyEasingLibrary::EaseInOutSine(const double Alpha)
{
	if (Alpha <= 0.f)
	{
		return 0.f;
	}

	if (Alpha >= 1.f)
	{
		return 1.f;
	}

	return (1.f - FMath::Cos(Alpha * PI)) * 0.5f;
}

double UTrickyEasingLibrary::EaseInQuad(const double Alpha)
{
	if (Alpha <= 0.f)
	{
		return 0.f;
	}

	if (Alpha >= 1.f)
	{
		return 1.f;
	}

	return Alpha * Alpha;
}

double UTrickyEasingLibrary::EaseOutQuad(const double Alpha)
{
	if (Alpha <= 0.f)
	{
		return 0.f;
	}

	if (Alpha >= 1.f)
	{
		return 1.f;
	}

	return 1.f - (1.f - Alpha) * (1.f - Alpha);
}

double UTrickyEasingLibrary::EaseInOutQuad(const double Alpha)
{
	if (Alpha <= 0.f)
	{
		return 0.f;
	}

	if (Alpha >= 1.f)
	{
		return 1.f;
	}

	return Alpha < 0.5f
		       ? 2.f * Alpha * Alpha
		       : 1.f - FMath::Pow(2.f - 2.f * Alpha, 2) * 0.5f;
}

double UTrickyEasingLibrary::EaseInCubic(const double Alpha)
{
	if (Alpha <= 0.f)
	{
		return 0.f;
	}

	if (Alpha >= 1.f)
	{
		return 1.f;
	}

	return Alpha * Alpha * Alpha;
}

double UTrickyEasingLibrary::EaseOutCubic(const double Alpha)
{
	if (Alpha <= 0.f)
	{
		return 0.f;
	}

	if (Alpha >= 1.f)
	{
		return 1.f;
	}

	return 1.f - FMath::Pow(1.f - Alpha, 3);
}

double UTrickyEasingLibrary::EaseInOutCubic(const double Alpha)
{
	if (Alpha <= 0.f)
	{
		return 0.f;
	}

	if (Alpha >= 1.f)
	{
		return 1.f;
	}

	return Alpha < 0.5 ? 4.f * Alpha * Alpha * Alpha : 1.f - FMath::Pow(-2.f * Alpha + 2.f, 3) * 0.5f;
}

double UTrickyEasingLibrary::EaseInQuart(const double Alpha)
{
	if (Alpha <= 0.f)
	{
		return 0.f;
	}

	if (Alpha >= 1.f)
	{
		return 1.f;
	}

	return Alpha * Alpha * Alpha * Alpha;
}

double UTrickyEasingLibrary::EaseOutQuart(const double Alpha)
{
	if (Alpha <= 0.f)
	{
		return 0.f;
	}

	if (Alpha >= 1.f)
	{
		return 1.f;
	}

	return 1.f - FMath::Pow(1.f - Alpha, 4);
}

double UTrickyEasingLibrary::EaseInOutQuart(const double Alpha)
{
	if (Alpha <= 0.f)
	{
		return 0.f;
	}

	if (Alpha >= 1.f)
	{
		return 1.f;
	}

	return Alpha < 0.5f
		       ? 8.f * Alpha * Alpha * Alpha * Alpha
		       : 1.f - FMath::Pow(2.f - 2.f * Alpha, 4) * 0.5f;
}

double UTrickyEasingLibrary::EaseInQuint(const double Alpha)
{
	if (Alpha <= 0.f)
	{
		return 0.f;
	}

	if (Alpha >= 1.f)
	{
		return 1.f;
	}

	return Alpha * Alpha * Alpha * Alpha * Alpha;
}

double UTrickyEasingLibrary::EaseOutQuint(const double Alpha)
{
	if (Alpha <= 0.f)
	{
		return 0.f;
	}

	if (Alpha >= 1.f)
	{
		return 1.f;
	}

	return 1.f - FMath::Pow(1.f - Alpha, 5);
}

double UTrickyEasingLibrary::EaseInOutQuint(const double Alpha)
{
	if (Alpha <= 0.f)
	{
		return 0.f;
	}

	if (Alpha >= 1.f)
	{
		return 1.f;
	}

	return Alpha < 0.5f
		       ? 16.f * Alpha * Alpha * Alpha * Alpha * Alpha
		       : 1.f - FMath::Pow(2.f - 2.f * Alpha, 5.f) * 0.5f;
}

double UTrickyEasingLibrary::EaseInCirc(const double Alpha)
{
	if (Alpha <= 0.f)
	{
		return 0.f;
	}

	if (Alpha >= 1.f)
	{
		return 1.f;
	}

	return 1.f - FMath::Sqrt(1.f - FMath::Pow(Alpha, 2));
}

double UTrickyEasingLibrary::EaseOutCirc(const double Alpha)
{
	if (Alpha <= 0.f)
	{
		return 0.f;
	}

	if (Alpha >= 1.f)
	{
		return 1.f;
	}

	return FMath::Sqrt(1.f - FMath::Pow(Alpha - 1.f, 2));
}

double UTrickyEasingLibrary::EaseInOutCirc(const double Alpha)
{
	if (Alpha <= 0.f)
	{
		return 0.f;
	}

	if (Alpha >= 1.f)
	{
		return 1.f;
	}

	return Alpha < 0.5f
		       ? (1.f - FMath::Sqrt(1.f - FMath::Pow(2.f * Alpha, 2))) * 0.5f
		       : (FMath::Sqrt(1.f - FMath::Pow(2.f - 2.f * Alpha, 2)) + 1) * 0.5f;
}

double UTrickyEasingLibrary::EaseInExpo(const double Alpha)
{
	if (Alpha <= 0.f)
	{
		return 0.f;
	}

	if (Alpha >= 1.f)
	{
		return 1.f;
	}

	return FMath::Pow(2.f, 10.f * (Alpha - 1.f));
}

double UTrickyEasingLibrary::EaseOutExpo(const double Alpha)
{
	if (Alpha <= 0.f)
	{
		return 0;
	}

	if (Alpha >= 1.f)
	{
		return 1.f;
	}

	return 1.f - FMath::Pow(2.f, -10.f * Alpha);
}

double UTrickyEasingLibrary::EaseInOutExpo(const double Alpha)
{
	if (Alpha <= 0.f)
	{
		return 0.f;
	}

	if (Alpha >= 1.f)
	{
		return 1.f;
	}

	return Alpha < 0.5f
		       ? FMath::Pow(2.f, 10.f * (2.f * Alpha - 1.f) - 1.f)
		       : 1.f - FMath::Pow(2.f, -10.f * (2.f * Alpha - 1.f) - 1.f);
}

double UTrickyEasingLibrary::EaseInBack(const double Alpha)
{
	constexpr double Overshoot = PI;

	if (Alpha <= 0.f)
	{
		return 0.f;
	}

	if (Alpha >= 1.f)
	{
		return 1.f;
	}

	return Alpha * Alpha * ((Overshoot + 1.f) * Alpha - Overshoot);
}

double UTrickyEasingLibrary::EaseOutBack(const double Alpha)
{
	const double X = Alpha - 1;
	constexpr double Overshoot = PI;

	if (Alpha <= 0.f)
	{
		return 0.f;
	}

	if (Alpha >= 1.f)
	{
		return 1.f;
	}

	return 1.f + X * X * (X * (Overshoot + 1.f) + Overshoot);
}

double UTrickyEasingLibrary::EaseInOutBack(const double Alpha)
{
	const double Alpha2 = Alpha * 2.f;
	constexpr double Overshoot = PI * 1.525;

	if (Alpha <= 0.f)
	{
		return 0.f;
	}

	if (Alpha >= 1.f)
	{
		return 1.f;
	}

	if (Alpha < 0.5f)
	{
		return Alpha * Alpha2 * (Alpha2 * (Overshoot + 1.f) - Overshoot);
	}

	const double X = Alpha - 1.f;
	return 1.f + 2 * X * X * (2.f * X * (Overshoot + 1.f) + Overshoot);
}

double UTrickyEasingLibrary::EaseInElastic(const double Alpha)
{
	const double X = Alpha - 1.f;

	if (Alpha <= 0.f)
	{
		return 0.f;
	}

	if (Alpha >= 1.f)
	{
		return 1.f;
	}

	return -FMath::Pow(2.f, 10.f * X) * FMath::Sin((X * 40.f - 3.f) * PI / 6.f);
}

double UTrickyEasingLibrary::EaseOutElastic(const double Alpha)
{
	if (Alpha <= 0.f)
	{
		return 0.f;
	}

	if (Alpha >= 1.f)
	{
		return 1.f;
	}

	return 1.f + FMath::Pow(2.f, 10.f * -Alpha) * FMath::Sin((-Alpha * 40.f - 3.f) * PI / 6.f);
}

double UTrickyEasingLibrary::EaseInOutElastic(const double Alpha)
{
	if (Alpha <= 0.f)
	{
		return 0.f;
	}

	if (Alpha >= 1.f)
	{
		return 1.f;
	}

	const double X = 2.f * Alpha - 1.f;

	const double k = (80.f * X - 9.f) * PI / 18.f;

	return X < 0.f
		       ? -0.5f * FMath::Pow(2.f, 10.f * X) * FMath::Sin(k)
		       : 1.f + 0.5f * FMath::Pow(2.f, -10.f * X) * FMath::Sin(k);
}

double UTrickyEasingLibrary::EaseInBounce(const double Alpha)
{
	if (Alpha <= 0.f)
	{
		return 0.f;
	}

	if (Alpha >= 1.f)
	{
		return 1.f;
	}

	return 1.f - EaseInBounce(1.f - Alpha);
}

double UTrickyEasingLibrary::EaseOutBounce(const double Alpha)
{
	double Alpha2 = 0.f;
	constexpr double Bounce_R = 1.0f / 2.75f;
	constexpr double Bounce_K1 = Bounce_R;
	constexpr double Bounce_K2 = 2 * Bounce_R;
	constexpr double Bounce_K3 = 1.5f * Bounce_R;
	constexpr double Bounce_K4 = 2.5f * Bounce_R;
	constexpr double Bounce_K5 = 2.25f * Bounce_R;
	constexpr double Bounce_K6 = 2.625f * Bounce_R;
	constexpr double Bounce_K0 = 7.5625f;

	if (Alpha <= 0.f)
	{
		return 0.f;
	}

	if (Alpha >= 1.f)
	{
		return 1.f;
	}

	if (Alpha < Bounce_K1)
	{
		return Bounce_K0 * Alpha * Alpha;
	}

	if (Alpha < Bounce_K2)
	{
		Alpha2 = Alpha - Bounce_K3;
		return Bounce_K0 * Alpha2 * Alpha2 + 0.75f;
	}

	if (Alpha < Bounce_K4)
	{
		Alpha2 = Alpha - Bounce_K5;
		return Bounce_K0 * Alpha2 * Alpha2 + 0.9375f;
	}

	Alpha2 = Alpha - Bounce_K6;
	return Bounce_K0 * Alpha2 * Alpha2 + 0.984375f;
}

double UTrickyEasingLibrary::EaseInOutBounce(const double Alpha)
{
	const double Alpha2 = Alpha * 2.f;

	if (Alpha <= 0.f)
	{
		return 0.f;
	}

	if (Alpha >= 1.f)
	{
		return 1.f;
	}

	return Alpha2 < 1.f
		       ? 0.5f - 0.5f * EaseOutBounce(1.f - Alpha2)
		       : 0.5f + 0.5f * EaseOutBounce(Alpha2 - 1.f);
}
