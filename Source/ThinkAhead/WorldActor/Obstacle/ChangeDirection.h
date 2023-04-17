// Copyright © 2023 Lee Mclafferty. All rights reserved. This code is the property of Lee Mclafferty and may not be used for resale, redistribution, or for the purpose of making a profit without written consent from the owner.

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

	bool bHasActivated;
};
