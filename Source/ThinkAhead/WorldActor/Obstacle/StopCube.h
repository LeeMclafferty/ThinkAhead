// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ThinkAhead/WorldActor/Obstacle/Obstacle.h"
#include "StopCube.generated.h"

/**
 * 
 */
UCLASS()
class THINKAHEAD_API AStopCube : public AObstacle
{
	GENERATED_BODY()

public:
	AStopCube();

	virtual void PerformAction() override;

protected:


	
};
