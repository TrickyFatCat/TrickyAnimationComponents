// MIT License Copyright. Created by Artyom "Tricky Fat Cat" Volkov


#include "Libraries/TrickyEasingLibrary.h"

double UTrickyEasingLibrary::EaseInSine(const double Alpha)
{
	return 1.f - FMath::Cos((Alpha * PI) / 2.f);
}

double UTrickyEasingLibrary::EaseOutSine(const double Alpha)
{
	return FMath::Sin((Alpha * PI) / 2.f);
}

double UTrickyEasingLibrary::EaseInOutSine(const double Alpha)
{
	return -(FMath::Cos(PI * Alpha) - 1.f) / 2.f;
}
