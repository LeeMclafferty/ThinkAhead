// Fill out your copyright notice in the Description page of Project Settings.

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

	void GenerateTileVerts(TArray<FVector>& Verts);
	void GenerateTrianles(TArray<int32>& Tris);

};
