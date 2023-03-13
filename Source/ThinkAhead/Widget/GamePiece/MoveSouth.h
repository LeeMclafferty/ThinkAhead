// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ThinkAhead/Widget/GamePiece/MovePiece.h"
#include "MoveSouth.generated.h"

/**
 * 
 */
UCLASS()
class THINKAHEAD_API UMoveSouth : public UMovePiece
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	void Move();
	
};
