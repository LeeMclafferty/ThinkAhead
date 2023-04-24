// Copyright © 2023 Lee Mclafferty. All rights reserved. This code is the property of Lee Mclafferty and may not be used for resale, redistribution, or for the purpose of making a profit without written consent from the owner.


#include "ThinkAhead/Gamemode/LevelGamemode.h"
#include "Kismet/GameplayStatics.h"

#include "ThinkAhead/Widget/GamePiece/MovePiece.h"
#include "ThinkAhead/Controller/CubeController.h"
#include "ThinkAhead/GameInstance/ThinkAheadGameInstance.h"

ALevelGamemode::ALevelGamemode()
:NumOfMovesToMake(4), NumMoveOptions(5)
{
	
}

void ALevelGamemode::BeginPlay()
{
	Super::BeginPlay();

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

	GameInst->UnlockLevel(NextLevelName);
	GameInst->SaveGame();
}