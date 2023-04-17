// Copyright © 2023 Lee Mclafferty. All rights reserved. This code is the property of Lee Mclafferty and may not be used for resale, redistribution, or for the purpose of making a profit without written consent from the owner.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GridTile.generated.h"

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

	void DestroyTile();
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Procedural Mesh")
	int32 TileSize;
	
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
};
