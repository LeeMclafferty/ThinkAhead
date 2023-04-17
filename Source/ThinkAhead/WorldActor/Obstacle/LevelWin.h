// Copyright © 2023 Lee Mclafferty. All rights reserved. This code is the property of Lee Mclafferty and may not be used for resale, redistribution, or for the purpose of making a profit without written consent from the owner.

#pragma once

#include "CoreMinimal.h"
#include "ThinkAhead/WorldActor/Obstacle/Obstacle.h"
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
	class AThinkAheadGameModeBase* GameMode;
};
