// MIT License Copyright. Created by Artyom "Tricky Fat Cat" Volkov

#include "EasingAnimationSceneComponent.h"
#include "GameFramework/Actor.h"

UEasingAnimationSceneComponent::UEasingAnimationSceneComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	UActorComponent::SetComponentTickEnabled(false);
	bWantsInitializeComponent = true;
}

void UEasingAnimationSceneComponent::InitializeComponent()
{
	Super::InitializeComponent();

	DeltaLocation = TargetLocation;
	DeltaRotation = TargetRotation;
	DeltaScale = TargetScale;
}

void UEasingAnimationSceneComponent::BeginPlay()
{
	Super::BeginPlay();

	if (bStartOnBeginPlay)
	{
		Start();
	}
}

void UEasingAnimationSceneComponent::TickComponent(float DeltaTime,
                                                   ELevelTick TickType,
                                                   FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bIsPlaying)
	{
		const float CurrentTime = GetWorld()->GetTimeSeconds() - LaunchTime;

		if (CurrentTime < Duration)
		{
			const float Alpha = CurrentTime / Duration;
			if (bAnimateLocation)
			{
				FVector NewLocation;
				EaseVector(NewLocation, InitialLocation, TargetLocation, Alpha);
				SetRelativeLocation(NewLocation);
			}

			if (bAnimateRotation)
			{
				FRotator NewRotation;
				EaseRotator(NewRotation, InitialRotation, TargetRotation, Alpha);
				SetRelativeRotation(NewRotation);
			}

			if (bAnimateScale)
			{
				FVector NewScale;
				EaseVector(NewScale, InitialScale, TargetScale, Alpha);
				SetRelativeScale3D(NewScale);
			}
		}
		else
		{
			Finish();
		}
	}
}

bool UEasingAnimationSceneComponent::GetIsPlaying() const
{
	return bIsPlaying;
}

void UEasingAnimationSceneComponent::Start()
{
	if (bIsPlaying)
	{
		return;
	}

	if (Duration <= 0.f)
	{
		UE_LOG(LogTemp, Error, TEXT("Ease animation duration is <= 0."));
	}

	LaunchTime = GetWorld()->GetTimeSeconds();
	InitialLocation = GetRelativeLocation();
	InitialRotation = GetRelativeRotation();
	InitialScale = GetRelativeScale3D();

	bIsPlaying = true;
	SetComponentTickEnabled(true);
	OnAnimationStarted.Broadcast();
}

void UEasingAnimationSceneComponent::Stop()
{
	if (!bIsPlaying)
	{
		return;
	}

	bIsPlaying = false;
	SetComponentTickEnabled(false);
	OnAnimationStopped.Broadcast();
}

float UEasingAnimationSceneComponent::GetEaseDuration() const
{
	return Duration;
}

void UEasingAnimationSceneComponent::SetEaseDuration(const float Value)
{
	if (Value < 0.f)
	{
		return;
	}

	Duration = Value;
}

FVector UEasingAnimationSceneComponent::GetTargetLocation() const
{
	return TargetLocation;
}

void UEasingAnimationSceneComponent::SetTargetLocation(const FVector& Value)
{
	TargetLocation = Value;
}

FRotator UEasingAnimationSceneComponent::GetTargetRotation() const
{
	return TargetRotation;
}

void UEasingAnimationSceneComponent::SetTargetRotation(const FRotator& Value)
{
	TargetRotation = Value;
}

FVector UEasingAnimationSceneComponent::GetTargetScale() const
{
	return TargetScale;
}

void UEasingAnimationSceneComponent::SetTargetScale(const FVector& Value)
{
	TargetScale = Value;
}

void UEasingAnimationSceneComponent::Finish()
{
	OnAnimationFinished.Broadcast();

	switch (AnimationBehavior)
	{
	case EEaseAnimBehavior::Normal:
		bIsPlaying = false;
		SetComponentTickEnabled(false);
		break;

	case EEaseAnimBehavior::Additive:
		InitialLocation = TargetLocation;
		InitialRotation = TargetRotation;
		InitialScale = TargetScale;

		TargetLocation = InitialLocation + DeltaLocation;
		TargetRotation = InitialRotation + DeltaRotation;
		TargetScale = InitialScale + DeltaScale;

		LaunchTime = GetWorld()->GetTimeSeconds();
		break;

	case EEaseAnimBehavior::PingPong:
		UTrickyAnimationComponentsLibrary::SwapValues<FVector>(InitialLocation, TargetLocation);
		UTrickyAnimationComponentsLibrary::SwapValues<FRotator>(InitialRotation, TargetRotation);
		UTrickyAnimationComponentsLibrary::SwapValues<FVector>(InitialScale, TargetScale);
		LaunchTime = GetWorld()->GetTimeSeconds();
		break;
	}
}

void UEasingAnimationSceneComponent::EaseVector(FVector& Value,
                                                const FVector& InitialValue,
                                                const FVector& TargetValue,
                                                const float Alpha) const
{
	UTrickyAnimationComponentsLibrary::EaseVector(Value,
	                                              InitialValue,
	                                              TargetValue,
	                                              Alpha,
	                                              EaseFunction,
	                                              BlendExp,
	                                              Steps);
}

void UEasingAnimationSceneComponent::EaseRotator(FRotator& Value,
                                                 const FRotator& InitialValue,
                                                 const FRotator& TargetValue,
                                                 const float Alpha) const
{
	UTrickyAnimationComponentsLibrary::EaseRotator(Value,
	                                               InitialValue,
	                                               TargetValue,
	                                               Alpha,
	                                               EaseFunction,
	                                               BlendExp,
	                                               Steps);
}
