// Fill out your copyright notice in the Description page of Project Settings.


#include "ThinkAhead/Gamemode/LevelGamemode.h"
#include "Kismet/GameplayStatics.h"

#include "ThinkAhead/Widget/GamePiece/MovePiece.h"
#include "ThinkAhead/Controller/CubeController.h"
#include "ThinkAhead/GameInstance/ThinkAheadGameInstance.h"

ALevelGamemode::ALevelGamemode()
:NumOfMovesToMake(4), NumMoveOptions(5)
{
	CreateStartingPieces();
}

void ALevelGamemode::BeginPlay()
{
	Super::BeginPlay();

	UnlockLevel();
	CreateStartingPieces();
}

void ALevelGamemode::CreateStartingPieces()
{
	UMovePiece* Current = nullptr;

	for (auto PieceClass : StartingPieceClasses)
	{
		if (PieceClass)
			Current = CreateWidget<UMovePiece>(GetWorld(), PieceClass);

		StaringPieces.Emplace(Current);
	}
}

void ALevelGamemode::LevelLost()
{
	auto Controller = Cast<ACubeController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	if (!Controller)
		return;

	Controller->CreateLoseScreen();
}

void ALevelGamemode::UnlockLevel()
{
	UThinkAheadGameInstance* GameInst = Cast<UThinkAheadGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (!GameInst)
		return;

	GameInst->UnlockLevel(LevelName);
	GameInst->SaveGame();
}