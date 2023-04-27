// Copyright © 2023 Lee Mclafferty. All rights reserved. This code is the property of Lee Mclafferty and may not be used for resale, redistribution, or for the purpose of making a profit without written consent from the owner.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class THINKAHEAD_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	AMyPlayerController();

	UFUNCTION(BlueprintCallable)
	void CreateLoseScreen();
	UFUNCTION(BlueprintCallable)
	void CreateWinScreen();
	UFUNCTION(BlueprintCallable)
	void CreateMainMenu();
	UFUNCTION(BlueprintCallable)
	void CreateLevelSelect();
	UFUNCTION(BlueprintCallable)
	void CreateExitPopup();
	UFUNCTION(BlueprintCallable)
	void CreateMainSettingsMenu();
	UFUNCTION(BlueprintCallable)
	void CreateGameSettingsMenu();
	UFUNCTION(BlueprintCallable)
	void CreatePreviousWidget();

	UFUNCTION(BlueprintPure)
	class UPlayerHud* GetPlayerHud() { return PlayerHud;}

protected:
	virtual void SetupInputComponent() override;

	void SetupWidget(TSubclassOf<UUserWidget> WidgetClass);
	virtual void Tick(float DeltaTime) override;

	void ClearViewPort();

	UUserWidget* GetCurrentWidget() { return CurrentWidget; }

	UPROPERTY(EditDefaultsOnly, Category = "Initialize|WidgetClass")
	TSubclassOf<UUserWidget> PlayerHudClass;
	class UPlayerHud* PlayerHud;

	UPROPERTY(EditDefaultsOnly, Category = "Initialize|WidgetClass")
	TSubclassOf<UUserWidget> LoseScreenClass;

	UPROPERTY(EditDefaultsOnly, Category = "Initialize|WidgetClass")
	TSubclassOf<UUserWidget> WinScreenClass;

	UPROPERTY(EditDefaultsOnly, Category = "Initialize|WidgetClass")
	TSubclassOf<class UUserWidget> MainMenuClass;

	UPROPERTY(EditDefaultsOnly, Category = "Initialize|WidgetClass")
	TSubclassOf<class UUserWidget> LevelSelectClass;

	UPROPERTY(EditDefaultsOnly, Category = "Initialize|WidgetClass")
	TSubclassOf<class UUserWidget> SettingsMainMenuClass;

	UPROPERTY(EditDefaultsOnly, Category = "Initialize|WidgetClass")
	TSubclassOf<class UUserWidget> SettingsGameClass;

	UPROPERTY(EditDefaultsOnly, Category = "Initialize|WidgetClass")
	TSubclassOf<class UUserWidget> ExitPopupClass;

	TSubclassOf<class UUserWidget> PreviousWidgetClass;
	
	UUserWidget* CurrentWidget;

	
};
