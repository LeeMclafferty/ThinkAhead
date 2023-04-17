// Copyright © 2023 Lee Mclafferty. All rights reserved. This code is the property of Lee Mclafferty and may not be used for resale, redistribution, or for the purpose of making a profit without written consent from the owner.

#pragma once

#include "CoreMinimal.h"
#include "ThinkAhead/WorldActor/Obstacle/KillSpace.h"
#include "Grill.generated.h"

/**
 * 
 */
UCLASS()
class THINKAHEAD_API AGrill : public AKillSpace
{
	GENERATED_BODY()

public:
	AGrill();

	virtual void PerformAction() override;
	
};
