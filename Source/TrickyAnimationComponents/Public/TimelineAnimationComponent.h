// MIT License Copyright (c) 2022 Artyom "Tricky Fat Cat" Volkov

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TimelineAnimationComponent.generated.h"

class UCurveFloat;
class UTimelineComponent;

UENUM(BlueprintType)
enum class ETimelineAnimationState: uint8
{
	Start,
	End,
	Transition UMETA(Hidden),
	Stopped	UMETA(Hdidden)
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAnimationStartedSignature, ETimelineAnimationState, TargetState);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAnimationReversedSignature, ETimelineAnimationState, NewTargetState);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAnimationFinishedSignature, ETimelineAnimationState, NewState);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAnimationStoppedSignature);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAnimationResumedSignature);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TRICKYANIMATIONCOMPONENTS_API UTimelineAnimationComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UTimelineAnimationComponent();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	UTimelineComponent* Timeline = nullptr;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Animation)
	ETimelineAnimationState InitialState = ETimelineAnimationState::Start;

	UPROPERTY(BlueprintAssignable, Category="TrickyAnimations|TimelineAnimation")
	FOnAnimationStartedSignature OnAnimationStarted;
	
	UPROPERTY(BlueprintAssignable, Category="TrickyAnimations|TimelineAnimation")
	FOnAnimationReversedSignature OnAnimationReversed;
	
	UPROPERTY(BlueprintAssignable, Category="TrickyAnimations|TimelineAnimation")
	FOnAnimationFinishedSignature OnAnimationFinished;

	UPROPERTY(BlueprintAssignable, Category="TrickyAnimations|TimelineAnimation")
	FOnAnimationStoppedSignature OnAnimationStopped;
	
	UPROPERTY(BlueprintAssignable, Category="TrickyAnimations|TimelineAnimation")
	FOnAnimationResumedSignature OnAnimationResumed;

	UFUNCTION(BlueprintCallable, Category="TrickyAnimations|TimelineAnimation")
	void Start();

	UFUNCTION(BlueprintCallable, Category="TrickyAnimations|TimelineAnimation")
	void Reverse();

	UFUNCTION(BlueprintCallable, Category="TrickyAnimations|TimelineAnimation")
	void Stop();

	UFUNCTION(BlueprintCallable, Category="TrickyAnimations|TimelineAnimation")
	void Resume();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Animation")
	bool bIsReversible = false;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Animation|States", meta=(AllowPrivateAccess="true"))
	ETimelineAnimationState CurrentState = InitialState;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Animation|States", meta=(AllowPrivateAccess="true"))
	ETimelineAnimationState TargetState = ETimelineAnimationState::End;

	UFUNCTION()
	void FinishAnimation();

};
