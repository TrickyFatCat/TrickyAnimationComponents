// MIT License Copyright. Created by Artyom "Tricky Fat Cat" Volkov


#include "Libraries/TrickyEasingLibrary.h"

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
