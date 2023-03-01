// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ThinkAhead/Widget/MovesContainer.h"
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
