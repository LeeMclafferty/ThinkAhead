// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ThinkAhead/WorldActor/Obstacle.h"
#include "LevelWin.generated.h"

UCLASS()
class THINKAHEAD_API ALevelWin : public AObstacle
{
	GENERATED_BODY()

public:

	ALevelWin();
	
	virtual void PerformAction() override;

private:

	class ACubeController* PlayerController;
};
