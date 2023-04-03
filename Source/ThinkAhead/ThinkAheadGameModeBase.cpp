// Copyright Epic Games, Inc. All Rights Reserved.


#include "ThinkAheadGameModeBase.h"
#include "Kismet/GameplayStatics.h"

#include "ThinkAhead/Widget/GamePiece/MovePiece.h"
#include "ThinkAhead/GameInstance/ThinkAheadGameInstance.h"
#include "ThinkAhead/Controller/CubeController.h"


AThinkAheadGameModeBase::AThinkAheadGameModeBase()
	:NumOfMovesToMake(4), NumMoveOptions(5), bIsOrtho(false)
{

}

void AThinkAheadGameModeBase::LevelLost()
{
	auto Controller = Cast<ACubeController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	if (!Controller)
		return;
	
	Controller->CreateLoseScreen();
}

void AThinkAheadGameModeBase::ToggleOrtho()
{
	if (bIsOrtho)
	{
		bIsOrtho = false;
	}
	else
	{
		bIsOrtho = true;
	}
}

void AThinkAheadGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	LoadGame();
	UnlockLevel();
	CreateStartingPieces();
}

void AThinkAheadGameModeBase::CreateStartingPieces()
{
	UMovePiece* Current = nullptr;

	for (auto PieceClass : StartingPieceClasses)
	{
		if(PieceClass)
			Current = CreateWidget<UMovePiece>(GetWorld(), PieceClass);

		StaringPieces.Emplace(Current);
	}
}

void AThinkAheadGameModeBase::UnlockLevel()
{
	UThinkAheadGameInstance* GameInst = Cast<UThinkAheadGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (!GameInst)
		return;

	GameInst->UnlockLevel(LevelName);
	GameInst->SaveGame();
}

void AThinkAheadGameModeBase::LoadGame()
{
	UThinkAheadGameInstance* GameInst = Cast<UThinkAheadGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (!GameInst)
		return;

	GameInst->LoadGame();
}
