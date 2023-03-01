// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CubeController.generated.h"

/**
 * 
 */
UCLASS()
class THINKAHEAD_API ACubeController : public APlayerController
{
	GENERATED_BODY()

public: 
	ACubeController();

	virtual void BeginPlay() override;
	class UExecuteMoves* GetExecuteButton() { return ExecuteButton; }

	void SetControlledCube(class AControlledCube* NewCube);

protected:

	void CreatePlayerHud();
	UPROPERTY(EditDefaultsOnly, Category = "Initialize")
	TSubclassOf<UUserWidget> PlayerHudClass;
	class UPlayerHud* PlayerHud;

private:
	class UExecuteMoves* ExecuteButton;
	class AControlledCube* ControlledCube;
	
};
