// MIT License Copyright (c) Artyom "Tricky Fat Cat" Volkov

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FollowAnimationComponent.generated.h"

/**
 * A component which interpolates an owning actor location towards a target location/actor.
*/
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TRICKYANIMATIONCOMPONENTS_API UFollowAnimationComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UFollowAnimationComponent();

	/**Toggles if the component will interpolate position towards a target actor or a specific location.*/
	UPROPERTY(EditAnywhere,
		BlueprintReadWrite,
		Category="Animation",
		meta=(DisplayAfter="bIsEnabled"))
	bool bFollowActor = true;

	/**An actor which world location will be used as a target location.*/
	UPROPERTY(EditAnywhere,
		BlueprintReadWrite,
		Category="Animation",
		meta=(DisplayAfter="bIsEnabled", EditCondition="bFollowActor", EditConditionHides))
	AActor* TargetActor = nullptr;

	/**The world location which will be used as a target location.*/
	UPROPERTY(EditAnywhere,
		BlueprintReadWrite,
		Category="Animation",
		meta=(DisplayAfter="bIsEnabled", EditCondition="!bFollowActor", EditConditionHides))
	FVector Location{FVector::ZeroVector};

	/**Location offset relative to the target location.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Animation", meta=(DisplayAfter="bIsEnabled"))
	FVector TargetLocationOffset{FVector::ZeroVector};

	/**Determines the speed of interpolation.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Animation", meta=(DisplayAfter="bIsEnabled"))
	float Speed = 5;

	/**Starts interpolation.*/
	UFUNCTION(BlueprintSetter, Category="TrickyAnimations|EaseAnimation")
	bool StartFollowing();

	/**Stops interpolation.*/
	UFUNCTION(BlueprintSetter, Category="TrickyAnimations|EaseAnimation")
	bool StopFollowing();

	UFUNCTION(BlueprintGetter, Category="TrickyAnimations|EaseAnimation")
	bool GetIsFollowing() const;

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime,
	                           ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(BlueprintGetter=GetIsFollowing,
		Category="Animation",
		meta=(AllowPrivateAccess))
	bool bIsFollowing = true;

	FVector CurrentLocation{FVector::ZeroVector};

	FVector TargetLocation{FVector::ZeroVector};

	FVector NewLocation{FVector::ZeroVector};
};
