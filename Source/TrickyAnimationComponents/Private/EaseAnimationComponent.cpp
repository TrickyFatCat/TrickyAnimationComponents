// MIT License Copyright. Created by Artyom "Tricky Fat Cat" Volkov

#include "EaseAnimationComponent.h"

#include "GameFramework/Actor.h"

UEaseAnimationComponent::UEaseAnimationComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	UActorComponent::SetComponentTickEnabled(false);
	bWantsInitializeComponent = true;
}

void UEaseAnimationComponent::InitializeComponent()
{
	Super::InitializeComponent();
	
	DeltaLocation = TargetLocation;
	DeltaRotation = TargetRotation;
	DeltaScale = TargetScale;
}

void UEaseAnimationComponent::BeginPlay()
{
	Super::BeginPlay();

	if (bStartOnBeginPlay)
	{
		Start();
	}
}

void UEaseAnimationComponent::TickComponent(float DeltaTime,
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
				GetOwner()->SetActorLocation(NewLocation);
			}

			if (bAnimateRotation)
			{
				FRotator NewRotation;
				EaseRotator(NewRotation, InitialRotation, TargetRotation, Alpha);
				GetOwner()->SetActorRotation(NewRotation);
			}

			if (bAnimateScale)
			{
				FVector NewScale;
				EaseVector(NewScale, InitialScale, TargetScale, Alpha);
				GetOwner()->SetActorScale3D(NewScale);
			}
		}
		else
		{
			Finish();
		}
	}
}

bool UEaseAnimationComponent::GetIsPlaying() const
{
	return bIsPlaying;
}

bool UEaseAnimationComponent::Start()
{
	if (bIsPlaying)
	{
		return false;
	}

	if (Duration <= 0.f)
	{
		UE_LOG(LogTemp, Error, TEXT("Ease animation duration is <= 0."));
		return false;
	}

	LaunchTime = GetWorld()->GetTimeSeconds();
	InitialLocation = GetOwner()->GetActorLocation();
	InitialRotation = GetOwner()->GetActorRotation();
	InitialScale = GetOwner()->GetActorScale3D();

	bIsPlaying = true;
	SetComponentTickEnabled(true);
	OnAnimationStarted.Broadcast();
	return true;
}

bool UEaseAnimationComponent::Stop()
{
	if (!bIsPlaying)
	{
		return false;
	}

	bIsPlaying = false;
	SetComponentTickEnabled(false);
	OnAnimationStopped.Broadcast();
	return true;
}

float UEaseAnimationComponent::GetEaseDuration() const
{
	return Duration;
}

void UEaseAnimationComponent::SetEaseDuration(const float Value)
{
	if (Value < 0.f)
	{
		return;
	}

	Duration = Value;
}

FVector UEaseAnimationComponent::GetTargetLocation() const
{
	return TargetLocation;
}

void UEaseAnimationComponent::SetTargetLocation(const FVector& Value)
{
	TargetLocation = Value;
}

FRotator UEaseAnimationComponent::GetTargetRotation() const
{
	return TargetRotation;
}

void UEaseAnimationComponent::SetTargetRotation(const FRotator& Value)
{
	TargetRotation = Value;
}

FVector UEaseAnimationComponent::GetTargetScale() const
{
	return TargetScale;
}

void UEaseAnimationComponent::SetTargetScale(const FVector& Value)
{
	TargetScale = Value;
}

void UEaseAnimationComponent::Finish()
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

void UEaseAnimationComponent::EaseVector(FVector& Value,
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

void UEaseAnimationComponent::EaseRotator(FRotator& Value,
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
