// Copyright © 2023 Lee Mclafferty. All rights reserved. This code is the property of Lee Mclafferty and may not be used for resale, redistribution, or for the purpose of making a profit without written consent from the owner.

#pragma once

#include "CoreMinimal.h"
#include "ThinkAhead/Widget/Move/MovesContainer.h"
#include "MoveToContainer.generated.h"

/**
 * 
 */
UCLASS()
class THINKAHEAD_API UMoveToContainer : public UMovesContainer
{
	GENERATED_BODY()

public:
	class UExecuteMoves* GetExecuteButton() { return ExecuteButton; }

protected:
	UPROPERTY(meta=(BindWidget))
	class UExecuteMoves* ExecuteButton;
	
};
