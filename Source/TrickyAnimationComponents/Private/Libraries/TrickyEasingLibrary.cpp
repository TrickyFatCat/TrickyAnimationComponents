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
		
	case EEaseType::InCubic:
		Result = EaseInCubic(Alpha);
		break;
		
	case EEaseType::OutCubic:
		Result = EaseOutCubic(Alpha);
		break;
		
	case EEaseType::InOutCubic:
		Result = EaseInOutCubic(Alpha);
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
