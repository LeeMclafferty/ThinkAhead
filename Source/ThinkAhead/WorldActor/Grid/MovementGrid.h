// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ThinkAhead/WorldActor/Grid/GridTile.h"
#include "MovementGrid.generated.h"

UCLASS()
class THINKAHEAD_API AMovementGrid : public AActor
{
	GENERATED_BODY()
	
public:	
	AMovementGrid();
	~AMovementGrid();
	virtual void Tick(float DeltaTime) override;
	virtual void OnConstruction(const FTransform& Transform) override;

	void SetNumRows(int32 Rows) { NumRows = Rows; }
	void SetNumColumns(int32 Columns) { NumColumns = Columns; }

	UFUNCTION(BlueprintPure, Category="Getter")
	TArray<class AGridTile*> GetTiles() { return Tiles; }


protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void Destroyed() override;

	UPROPERTY(EditAnywhere, Category = "Grid|Generation")
	int32 TileSize;
	UPROPERTY(EditAnywhere, Category = "Grid|Generation")
	int32 NumRows; // Height
	UPROPERTY(EditAnywhere, Category = "Grid|Generation")
	int32 NumColumns; // Width
	UPROPERTY(EditAnywhere, Category = "Grid|Generation")
	bool bGenerateNew;
	UPROPERTY(EditAnywhere, Category = "Grid|Generation")
	bool bClearGrid; 

private:

	UPROPERTY(VisibleAnywhere)
	class USphereComponent* Orgin;
	
	UPROPERTY(EditDefaultsOnly, Category="Grid|Initilization")
	TSubclassOf<class AGridTile> TileClass;
	UPROPERTY(SaveGame, VisibleAnywhere)
	TArray<class AGridTile*> Tiles;
	
	void GenerateGrid();
	void DestroyGrid();
	void CreateNewGrid();

	UPROPERTY(EditDefaultsOnly, Category = "Grid|Initilization")
	class UMaterialInterface* FirstMaterial;
	UPROPERTY(EditDefaultsOnly, Category = "Grid|Initilization")
	class UMaterialInterface* SecondMaterial;

	UPROPERTY(VisibleAnywhere)
	bool bHasGridMade;

};
