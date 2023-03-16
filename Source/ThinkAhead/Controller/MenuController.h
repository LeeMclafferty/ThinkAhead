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

	void CreateMainMenu();
	void CreateLevelSelect();
	void CreateQuitPopup();
	void CreateOptionsMenu();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category="Init")
	TSubclassOf<class UUserWidget> MainMenuClass;
	UPROPERTY(EditDefaultsOnly, Category = "Init")
	TSubclassOf<class UUserWidget> LevelSelectClass;
	UPROPERTY(EditDefaultsOnly, Category = "Init")
	TSubclassOf<class UUserWidget> OptionsMenuClass;
	UPROPERTY(EditDefaultsOnly, Category = "Init")
	TSubclassOf<class UUserWidget> ExitPopupClass;

};
