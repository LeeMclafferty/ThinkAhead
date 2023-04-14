// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ThinkAhead/Controller/MyPlayerController.h"
#include "CubeController.generated.h"

/**
 * 
 */
UCLASS()
class THINKAHEAD_API ACubeController : public AMyPlayerController
{
	GENERATED_BODY()

public: 
	ACubeController();

	virtual void BeginPlay() override;
	class UExecuteMoves* GetExecuteButton() { return ExecuteButton; }
	class AControlledCube* GetControlledCube() { return ControlledCube; }

	void SetControlledCube(class AControlledCube* NewCube);

protected:


private:
	class UExecuteMoves* ExecuteButton;
	UPROPERTY(VisibleAnywhere)
	class AControlledCube* ControlledCube;
	
};
