// Copyright © 2023 Lee Mclafferty. All rights reserved. This code is the property of Lee Mclafferty and may not be used for resale, redistribution, or for the purpose of making a profit without written consent from the owner.


#include "ThinkAhead/Controller/MyPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

#include "ThinkAhead/Widget/Screen/PlayerHud.h"
#include "ThinkAhead/ThinkAheadGameModeBase.h"
#include "ThinkAhead/Widget/Menu/OptionsMenu.h"
#include "ThinkAhead/Widget/Screen/WinScreen.h"
#include "ThinkAhead/Widget/Screen/LoseScreen.h"

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

	ULoseScreen* Screen = Cast<ULoseScreen>(CurrentWidget);
	if (Screen)
		Screen->PlayLoseSound();
}

void AMyPlayerController::CreateWinScreen()
{
	SetupWidget(WinScreenClass);

	UWinScreen* Screen = Cast<UWinScreen>(CurrentWidget);
	if (Screen)
		Screen->PlayWinSound();
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

	FInputModeGameAndUI InputMode;
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputMode.SetHideCursorDuringCapture(false);
	SetInputMode(InputMode);

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
