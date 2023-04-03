// Fill out your copyright notice in the Description page of Project Settings.


#include "ThinkAhead/Controller/MyPlayerController.h"
#include "Blueprint/UserWidget.h"

#include "ThinkAhead/Widget/Screen/PlayerHud.h"

AMyPlayerController::AMyPlayerController()
{

}

void AMyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (InputComponent)
	{
		InputComponent->BindAction("OpenMenu", IE_Pressed, this, &AMyPlayerController::OpenSettingsMenu);
	}
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
	PreviousWidgetClass = PlayerHudClass;

// 	if (PreviousWidgetClass)
// 		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, FString::Printf(TEXT("CreatePlayerHud")));
}

void AMyPlayerController::OpenSettingsMenu()
{
	CreateSettingsMenu();
}

void AMyPlayerController::CreateMainMenu()
{
	SetupWidget(MainMenuClass);
	PreviousWidgetClass = MainMenuClass;
}

void AMyPlayerController::CreateLevelSelect()
{
	SetupWidget(LevelSelectClass);
}

void AMyPlayerController::CreateExitPopup()
{
	SetupWidget(ExitPopupClass);
}

void AMyPlayerController::CreateSettingsMenu()
{
	SetupWidget(SettingsMenuClass);
}

void AMyPlayerController::CreatePreviousWidget()
{
	if (!PreviousWidgetClass)
		return;

	SetupWidget(PreviousWidgetClass);
}
