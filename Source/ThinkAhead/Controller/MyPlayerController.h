// Fill out your copyright notice in the Description page of Project Settings.

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
	void CreateOptionsMenu();

protected:
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
	TSubclassOf<class UUserWidget> OptionsMenuClass;

	UPROPERTY(EditDefaultsOnly, Category = "Initialize|WidgetClass")
	TSubclassOf<class UUserWidget> ExitPopupClass;

	void CreatePlayerHud();
private:
	UUserWidget* CurrentWidget;
	
};
