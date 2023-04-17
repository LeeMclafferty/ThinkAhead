// Copyright � 2023 Lee Mclafferty. All rights reserved. This code is the property of Lee Mclafferty and may not be used for resale, redistribution, or for the purpose of making a profit without written consent from the owner.

#pragma once

#include "CoreMinimal.h"
#include "ThinkAhead/Widget/GamePiece/MovePiece.h"
#include "MoveWest.generated.h"

/**
 * 
 */
UCLASS()
class THINKAHEAD_API UMoveWest : public UMovePiece
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	void Move();
	
private:
};
