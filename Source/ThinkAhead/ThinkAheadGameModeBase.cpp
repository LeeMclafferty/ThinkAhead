// Copyright Epic Games, Inc. All Rights Reserved.


#include "ThinkAheadGameModeBase.h"
#include "Kismet/GameplayStatics.h"

#include "ThinkAhead/Widget/GamePiece/MovePiece.h"
#include "ThinkAhead/SaveGame/LevelSave.h"

AThinkAheadGameModeBase::AThinkAheadGameModeBase()
	:NumOfMovesToMake(4), NumMoveOptions(5), bHasWonLevel(false)
{

}

void AThinkAheadGameModeBase::WinLevel()
{
	bHasWonLevel = true;
}

void AThinkAheadGameModeBase::SaveGame()
{
	ULevelSave* LevelSave = Cast<ULevelSave>(UGameplayStatics::CreateSaveGameObject(ULevelSave::StaticClass()));

	TArray<AActor*> FoundTiles;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AGridTile::StaticClass(), FoundTiles);

	for (AActor* Tile : FoundTiles)
	{
		AGridTile* Current = Cast<AGridTile>(Tile);
		LevelSave->GridTiles.Add(Current);
	}

	UGameplayStatics::SaveGameToSlot(LevelSave, "Default", 0);
}

void AThinkAheadGameModeBase::LoadGame()
{
// 	ULevelSave* LevelSave = Cast<ULevelSave>(UGameplayStatics::CreateSaveGameObject(ULevelSave::StaticClass()));
// 	LevelSave = Cast<ULevelSave>(UGameplayStatics::LoadGameFromSlot("SaveSlot", 0));
// 
// 	if (LevelSave)
// 	{
// 		TArray<AGridTile*> LoadedTiles = LevelSave->GridTiles;
// 
// 		for (AGridTile* LoadedTile : LoadedTiles)
// 		{
// 			AGridTile* NewTile = GetWorld()->SpawnActor<AGridTile>(LoadedTile->GetClass());
// 			NewTile->TileType = LoadedTile->TileType;
// 			NewTile->HandleSpawning();
// 		}
// 	}

}

void AThinkAheadGameModeBase::BeginPlay()
{
	Super::BeginPlay();

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
