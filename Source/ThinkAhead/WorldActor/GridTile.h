// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GridTile.generated.h"


UENUM()
enum class ETileType : uint8 
{
	ETT_None UMETA(DisplayName="None"),
	ETT_Start UMETA(DisplayName="Start"),
	ETT_StopCube UMETA(DisplayName="StopCube")
};

UCLASS()
class THINKAHEAD_API AGridTile : public AActor
{
	GENERATED_BODY()

public:
	AGridTile();
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintPure)
	FVector GetTileCenter();
	UFUNCTION(BlueprintPure)
	int32 GetTileSize() { return TileSize; }
	
	void SetTileColor(class UMaterialInterface* Material);
	void SetTileSize(int32 NewTileSize) { TileSize = NewTileSize; }
	void SetTileType(ETileType NewType) { TileType = NewType; }

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Procedural Mesh")
	int32 TileSize;
	UPROPERTY(EditAnywhere, Category = "Procedural Mesh")
	ETileType TileType;

private:
	virtual void OnConstruction(const FTransform& Transform) override;

	UPROPERTY(VisibleAnywhere)
	class UProceduralMeshComponent* TileMesh;

	// Set Width/Height by changing TileSize
	int32 Width;
	int32 Height;

	UPROPERTY(SaveGame)
	TArray<FVector> Verticies;
	UPROPERTY(SaveGame)
	TArray<int32> Triangles;

	void GenerateTileVerts(TArray<FVector>& Verts);
	void GenerateTrianles(TArray<int32>& Tris);

	void HandleSpawning();

	void SpawnPlayersCube();
	void SpawnStopCube();

	UPROPERTY(EditDefaultsOnly, Category = "Tile|Initilization")
	TSubclassOf<class AControlledCube> ControlledCubeClass;
	UPROPERTY(EditDefaultsOnly, Category = "Tile|Initilization")
	TSubclassOf<class AStopCube> StopCubeClass;

	class ACameraPawn* PlayerPawn;
	void SetPlayerPawnRef();

};
