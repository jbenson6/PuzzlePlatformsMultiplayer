// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "MovingPlatform.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEMULTIPLAYER_API AMovingPlatform : public AStaticMeshActor
{
	GENERATED_BODY()
	

public:
	AMovingPlatform();

	void BeginPlay() override;

	void AddActiveTrigger();
	void RemoveActiveTrigger();

protected:
	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	float Speed = 10000.f;

	UPROPERTY(EditAnywhere, Meta = (MakeEditWidget = true))
	FVector TargetLocation;

	

private:
		FVector GlobalStartLocation;
		FVector GlobalTargetLocation;

		UPROPERTY(EditAnywhere)
		int ActiveTriggers = 1;


};
