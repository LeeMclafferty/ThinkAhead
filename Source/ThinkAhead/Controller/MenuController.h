// Copyright © 2023 Lee Mclafferty. All rights reserved. This code is the property of Lee Mclafferty and may not be used for resale, redistribution, or for the purpose of making a profit without written consent from the owner.

#pragma once

#include "CoreMinimal.h"
#include "ThinkAhead/Controller/MyPlayerController.h"
#include "MenuController.generated.h"

/**
 * 
 */
UCLASS()
class THINKAHEAD_API AMenuController : public AMyPlayerController
{
	GENERATED_BODY()
	
public:
	AMenuController();

protected:
	virtual void BeginPlay() override;



};
