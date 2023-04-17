// Copyright © 2023 Lee Mclafferty. All rights reserved. This code is the property of Lee Mclafferty and may not be used for resale, redistribution, or for the purpose of making a profit without written consent from the owner.

#pragma once

#include "CoreMinimal.h"
#include "ThinkAhead/ThinkAheadGameModeBase.h"
#include "MenuGameMode.generated.h"

/**
 * 
 */
UCLASS()
class THINKAHEAD_API AMenuGameMode : public AThinkAheadGameModeBase
{
	GENERATED_BODY()

public:

	AMenuGameMode();

protected:

	virtual void BeginPlay() override;
	
};
