// Copyright Epic Games, Inc. All Rights Reserved.


#include "ThinkAheadGameModeBase.h"

#include "ThinkAhead/Widget/MovePiece.h"

AThinkAheadGameModeBase::AThinkAheadGameModeBase()
	:NumOfMovesToMake(4), NumMoveOptions(5)
{
	StaringPieces.SetNum(NumMoveOptions);
}

void AThinkAheadGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("GM BeginPlay"));
	CreateStartingPieces();
}

void AThinkAheadGameModeBase::CreateStartingPieces()
{
	UMovePiece* Current;

	for (auto PieceClass : StartingPieceClasses)
	{
		Current = CreateWidget<UMovePiece>(GetWorld(), PieceClass);

		StaringPieces.Add(Current);
	}
}
