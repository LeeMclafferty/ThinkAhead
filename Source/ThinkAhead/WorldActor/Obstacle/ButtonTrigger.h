// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ThinkAhead/WorldActor/Obstacle/StopCube.h"
#include "ButtonTrigger.generated.h"

/**
 * 
 */
UCLASS()
class THINKAHEAD_API AButtonTrigger : public AStopCube
{
	GENERATED_BODY()
	
public:
	AButtonTrigger();

	void PerformAction() override;
	AObstacle* GetToInteractWith() { return ToInteractWith; }

private:
	bool bHasTriggered;
	UPROPERTY(EditAnywhere, Category="Init")
	AObstacle* ToInteractWith;

};
