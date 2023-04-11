// Fill out your copyright notice in the Description page of Project Settings.

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
