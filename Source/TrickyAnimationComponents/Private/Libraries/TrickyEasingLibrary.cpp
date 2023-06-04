// MIT License Copyright. Created by Artyom "Tricky Fat Cat" Volkov


#include "Libraries/TrickyEasingLibrary.h"

double UTrickyEasingLibrary::Ease(const EEaseType EaseType, const double Alpha)
{
	double Result = 0.f;
	switch (EaseType)
	{
	case EEaseType::Linear:
		Result = Alpha;
		break;

	case EEaseType::InSine:
		Result = EaseInSine(Alpha);
		break;

	case EEaseType::OutSine:
		Result = EaseOutSine(Alpha);
		break;

	case EEaseType::InOutSine:
		Result = EaseInOutSine(Alpha);
		break;

	case EEaseType::InQuad:
		Result = EaseInQuad(Alpha);
		break;

	case EEaseType::OutQuad:
		Result = EaseOutQuad(Alpha);
		break;

	case EEaseType::InOutQuad:
		Result = EaseInOutQuad(Alpha);
		break;

	case EEaseType::InCubic:
		Result = EaseInCubic(Alpha);
		break;

	case EEaseType::OutCubic:
		Result = EaseOutCubic(Alpha);
		break;

	case EEaseType::InOutCubic:
		Result = EaseInOutCubic(Alpha);
		break;

	case EEaseType::InQuart:
		Result = EaseInQuart(Alpha);
		break;

	case EEaseType::OutQuart:
		Result = EaseOutQuart(Alpha);
		break;

	case EEaseType::InOutQuart:
		Result = EaseInOutQuart(Alpha);
		break;
		
	case EEaseType::InQuint:
		Result = EaseInQuint(Alpha);
		break;

	case EEaseType::OutQuint:
		Result = EaseOutQuint(Alpha);
		break;

	case EEaseType::InOutQuint:
		Result = EaseInOutQuint(Alpha);
		break;

	case EEaseType::InCirc:
		Result = EaseInCirc(Alpha);
		break;

	case EEaseType::OutCirc:
		Result = EaseOutCirc(Alpha);
		break;

	case EEaseType::InOutCirc:
		Result = EaseInOutCirc(Alpha);
		break;

	default: ;
	}

	return Result;
}

double UTrickyEasingLibrary::EaseInSine(const double Alpha)
{
	return 1.f - FMath::Cos((Alpha * PI) * 0.5f);
}

double UTrickyEasingLibrary::EaseOutSine(const double Alpha)
{
	return FMath::Sin((Alpha * PI) * 0.5f);
}

double UTrickyEasingLibrary::EaseInOutSine(const double Alpha)
{
	return (1.f - FMath::Cos(Alpha * PI)) * 0.5f;
}

double UTrickyEasingLibrary::EaseInQuad(const double Alpha)
{
	return Alpha * Alpha;
}

double UTrickyEasingLibrary::EaseOutQuad(const double Alpha)
{
	return 1.f - (1.f - Alpha) * (1.f - Alpha);
}

double UTrickyEasingLibrary::EaseInOutQuad(const double Alpha)
{
	return Alpha < 0.5f
		       ? 2.f * Alpha * Alpha
		       : 1.f - FMath::Pow(2.f - 2.f * Alpha, 2) * 0.5f;
}

double UTrickyEasingLibrary::EaseInCubic(const double Alpha)
{
	return Alpha * Alpha * Alpha;
}

double UTrickyEasingLibrary::EaseOutCubic(const double Alpha)
{
	return 1.f - FMath::Pow(1.f - Alpha, 3);
}

double UTrickyEasingLibrary::EaseInOutCubic(const double Alpha)
{
	return Alpha < 0.5 ? 4.f * Alpha * Alpha * Alpha : 1.f - FMath::Pow(-2.f * Alpha + 2.f, 3) * 0.5f;
}

double UTrickyEasingLibrary::EaseInQuart(const double Alpha)
{
	return Alpha * Alpha * Alpha * Alpha;
}

double UTrickyEasingLibrary::EaseOutQuart(const double Alpha)
{
	return 1.f - FMath::Pow(1.f - Alpha, 4);
}

double UTrickyEasingLibrary::EaseInOutQuart(const double Alpha)
{
	return Alpha < 0.5f
		       ? 8.f * Alpha * Alpha * Alpha * Alpha
		       : 1.f - FMath::Pow(2.f - 2.f * Alpha, 4) * 0.5f;
}

double UTrickyEasingLibrary::EaseInQuint(const double Alpha)
{
	return Alpha * Alpha * Alpha * Alpha * Alpha;
}

double UTrickyEasingLibrary::EaseOutQuint(const double Alpha)
{
	return 1.f - FMath::Pow(1.f - Alpha, 5);
}

double UTrickyEasingLibrary::EaseInOutQuint(const double Alpha)
{
	return Alpha < 0.5f
		       ? 16.f * Alpha * Alpha * Alpha * Alpha * Alpha
		       : 1.f - FMath::Pow(2.f - 2.f * Alpha, 5.f) * 0.5f;
}

double UTrickyEasingLibrary::EaseInCirc(const double Alpha)
{
	return 1.f - FMath::Sqrt(1.f - FMath::Pow(Alpha, 2));
}

double UTrickyEasingLibrary::EaseOutCirc(const double Alpha)
{
	return FMath::Sqrt(1.f - FMath::Pow(Alpha - 1.f, 2));
}

double UTrickyEasingLibrary::EaseInOutCirc(const double Alpha)
{
	return Alpha < 0.5f
		       ? (1.f - FMath::Sqrt(1.f - FMath::Pow(2.f * Alpha, 2))) * 0.5f
		       : (FMath::Sqrt(1.f - FMath::Pow(2.f - 2.f * Alpha, 2)) + 1) * 0.5f;
}
