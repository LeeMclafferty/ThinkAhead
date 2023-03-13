// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ThinkAhead/WorldActor/Obstacle/Obstacle.h"
#include "KillSpace.generated.h"

UCLASS()
class THINKAHEAD_API AKillSpace : public AObstacle
{
	GENERATED_BODY()

public:

	AKillSpace();

	virtual void PerformAction() override;

private:

	class ACubeController* PlayerController;
	
};
