// Fill out your copyright notice in the Description page of Project Settings.

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
