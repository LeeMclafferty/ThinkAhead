// Fill out your copyright notice in the Description page of Project Settings.


#include "ThinkAhead/Widget/Screen/PlayerHud.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"

#include "ThinkAhead/Pawn/CameraPawn.h"
#include "ThinkAhead/Controller/CubeController.h"
#include "ThinkAhead/Widget/Move/MovesContainer.h"
#include "ThinkAhead/Widget/Move/MoveToContainer.h"
#include "ThinkAhead/ThinkAheadGameModeBase.h"


void UPlayerHud::NativeConstruct()
{
	Super::NativeConstruct();

	if (ACameraPawn* PP = Cast<ACameraPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0)))
	{
		PlayerPawn = PP;
	}

	ExecuteButton = MoveToPanel->GetExecuteButton();
}


 
void UPlayerHud::ResartLevel()
{
	auto Gamemode = Cast<AThinkAheadGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

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
