// Copyright © 2023 Lee Mclafferty. All rights reserved. This code is the property of Lee Mclafferty and may not be used for resale, redistribution, or for the purpose of making a profit without written consent from the owner.

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
