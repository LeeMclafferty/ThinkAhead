// Copyright Epic Games, Inc. All Rights Reserved.


#include "ThinkAheadGameModeBase.h"

#include "ThinkAhead/Widget/MovePiece.h"

AThinkAheadGameModeBase::AThinkAheadGameModeBase()
	:NumOfMovesToMake(4), NumMoveOptions(5)
{

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
