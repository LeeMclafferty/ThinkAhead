// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ThinkAhead/Widget/MovePiece.h"
#include "MoveForward.generated.h"

/**
 * 
 */
UCLASS()
class THINKAHEAD_API UMoveForward : public UMovePiece
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	void Move();

protected:

	
};
