// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ThinkAheadGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class THINKAHEAD_API AThinkAheadGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	AThinkAheadGameModeBase();

	UFUNCTION(BlueprintPure)
	int32 GetNumMovestoMake() { return NumOfMovesToMake; }
	UFUNCTION(BlueprintPure)
	int32 GetNumMoveOptions() { return NumMoveOptions; }
	UFUNCTION(BlueprintPure)
	TArray<class UMovePiece*> GetStartingPieces() { return StaringPieces; }
	UFUNCTION(BlueprintPure)
	FName GetLevelName() { return LevelName;}
	UFUNCTION(BlueprintPure)
	FName GetNextLevelName() { return NextLevelName; }

protected:

	virtual void BeginPlay() override;
	// Total Number of moves that can be executed for a level.
	UPROPERTY(EditDefaultsOnly, Category = "Initialization")
	int32 NumOfMovesToMake;

	// All of the possible moves to select from. 
	UPROPERTY(EditDefaultsOnly, Category = "Initialization")
	int32 NumMoveOptions;

	UPROPERTY(EditDefaultsOnly, Category = "Initialization|TSubclassOf")
	TArray<TSubclassOf<class UMovePiece>> StartingPieceClasses;

	UPROPERTY(VisibleAnywhere)
	TArray<class UMovePiece*> StaringPieces;

	UPROPERTY(EditDefaultsOnly, Category = "Initialization")
	FName LevelName;
	UPROPERTY(EditDefaultsOnly, Category = "Initialization")
	FName NextLevelName;
private:
	void CreateStartingPieces();
	
};
