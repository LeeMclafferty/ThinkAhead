// Fill out your copyright notice in the Description page of Project Settings.


#include "ThinkAhead/Controller/MyPlayerController.h"
#include "Blueprint/UserWidget.h"

#include "ThinkAhead/Widget/Screen/PlayerHud.h"

AMyPlayerController::AMyPlayerController()
{

}

void AMyPlayerController::SetupWidget(TSubclassOf<UUserWidget> WidgetClass)
{
	if (!WidgetClass)
		return;


	ClearViewPort();

	auto Menu = CreateWidget<UUserWidget>(this, WidgetClass);

	CurrentWidget = Menu;
	CurrentWidget->AddToViewport();

}

void AMyPlayerController::CreateLoseScreen()
{
	SetupWidget(LoseScreenClass);
}

void AMyPlayerController::CreateWinScreen()
{
	SetupWidget(WinScreenClass);
}

void AMyPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMyPlayerController::ClearViewPort()
{
	if (CurrentWidget)
		CurrentWidget->RemoveFromParent();
}

void AMyPlayerController::CreatePlayerHud()
{
	SetupWidget(PlayerHudClass);
	PlayerHud = Cast<UPlayerHud>(CurrentWidget);
}

void AMyPlayerController::CreateMainMenu()
{
	SetupWidget(MainMenuClass);
}

void AMyPlayerController::CreateLevelSelect()
{
	SetupWidget(LevelSelectClass);
}

void AMyPlayerController::CreateExitPopup()
{
	SetupWidget(ExitPopupClass);
}

void AMyPlayerController::CreateOptionsMenu()
{
	SetupWidget(OptionsMenuClass);
}