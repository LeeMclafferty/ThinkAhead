// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ThinkAhead/WorldActor/Obstacle/Obstacle.h"
#include "ChangeDirection.generated.h"

/**
 * 
 */
UCLASS()
class THINKAHEAD_API AChangeDirection : public AObstacle
{
	GENERATED_BODY()
	
public:
	AChangeDirection();

	void PerformAction() override;

private:

	UPROPERTY(EditDefaultsOnly, Category="Initialize")
	TSubclassOf<class UMovePiece> MoveClass;

	class UMovePiece* MoveDirection;
};
