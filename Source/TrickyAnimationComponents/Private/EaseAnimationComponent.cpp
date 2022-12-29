// MIT License Copyright (c) 2022 Artyom "Tricky Fat Cat" Volkov


#include "EaseAnimationComponent.h"
#include "GameFramework/Actor.h"

UEaseAnimationComponent::UEaseAnimationComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	UActorComponent::SetComponentTickEnabled(false);
}

void UEaseAnimationComponent::BeginPlay()
{
	Super::BeginPlay();
	SetIsEnabled(bIsEnabled);
}

void UEaseAnimationComponent::TickComponent(float DeltaTime,
                                            ELevelTick TickType,
                                            FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (TargetActor || !bFollowActor)
	{
		TargetLocation = bFollowActor ? TargetActor->GetActorLocation() : SpecificLocation;
		TargetLocation += LocationOffset;
		NewLocation.X = EaseAxis(InitialLocation.X, TargetLocation.X);
		NewLocation.Y = EaseAxis(InitialLocation.Y, TargetLocation.Y);
		NewLocation.Z = EaseAxis(InitialLocation.Z, TargetLocation.Z);
		GetOwner()->SetActorLocation(NewLocation);
	}
}

bool UEaseAnimationComponent::GetIsEnabled() const
{
	return bIsEnabled;
}

void UEaseAnimationComponent::SetIsEnabled(const bool Value)
{
	if (EaseDuration <= 0.f)
	{
		UE_LOG(LogTemp, Error, TEXT("Can't start ease animation because duration is < 0"));
		EaseDuration = 1.f;
	}

	bIsEnabled = Value;
	SetComponentTickEnabled(bIsEnabled);

	if (!GetWorld() || !bIsEnabled)
	{
		return;
	}

	LaunchTime = GetWorld()->GetTimeSeconds();
	InitialLocation = GetOwner()->GetActorLocation();
}

float UEaseAnimationComponent::GetEaseDuration() const
{
	return EaseDuration;
}

void UEaseAnimationComponent::SetEaseDuration(const float Value)
{
	if (Value < 0.f)
	{
		return;
	}

	EaseDuration = Value;
}

float UEaseAnimationComponent::EaseAxis(const float InitialValue,
                                        const float TargetValue)
{
	const float CurrentTime = GetWorld()->GetTimeSeconds();

	if (CurrentTime - LaunchTime < EaseDuration)
	{
		const float Alpha = (CurrentTime - LaunchTime) / EaseDuration;
		return UKismetMathLibrary::Ease(InitialValue,
		                                TargetValue,
		                                Alpha,
		                                EasingFunction,
		                                Exponent,
		                                SubStep);
	}

	SetIsEnabled(false);
	return TargetValue;
}
