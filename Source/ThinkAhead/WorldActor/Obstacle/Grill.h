// Fill out your copyright notice in the Description page of Project Settings.

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
