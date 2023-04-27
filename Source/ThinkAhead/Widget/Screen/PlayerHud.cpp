// Copyright © 2023 Lee Mclafferty. All rights reserved. This code is the property of Lee Mclafferty and may not be used for resale, redistribution, or for the purpose of making a profit without written consent from the owner.


#include "ThinkAhead/Widget/Screen/PlayerHud.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"

#include "ThinkAhead/Pawn/CameraPawn.h"
#include "ThinkAhead/Controller/CubeController.h"
#include "ThinkAhead/Widget/Move/MovesContainer.h"
#include "ThinkAhead/Widget/Move/MoveToContainer.h"
#include "ThinkAhead/Gamemode/LevelGamemode.h"


void UPlayerHud::NativeConstruct()
{
	Super::NativeConstruct();

	if (ACameraPawn* PP = Cast<ACameraPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0)))
	{
		PlayerPawn = PP;
	}
	PopulateGamePieces();
	SetControllerExecuteButton();
	ExecuteButton = MoveToPanel->GetExecuteButton();
}

void UPlayerHud::ResartLevel()
{
	auto Gamemode = Cast<ALevelGamemode>(UGameplayStatics::GetGameMode(GetWorld()));

	if (!Gamemode)
		return;

	UGameplayStatics::OpenLevel(GetWorld(), Gamemode->GetLevelName());
}

void UPlayerHud::SwapPerspective()
{
	if (!PlayerPawn)
		return;

	PlayerPawn->ChangePerspctive();
}

void UPlayerHud::PopulateGamePieces()
{
	auto Gamemode = Cast<ALevelGamemode>(UGameplayStatics::GetGameMode(GetWorld()));

	if (!Gamemode)
		return;

	Gamemode->CreateStartingPieces();
}

void UPlayerHud::SetControllerExecuteButton()
{
	auto Controller = Cast<ACubeController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	if (!Controller)
		return;

	Controller->SetExecuteButton(GetExecuteButton());
}
