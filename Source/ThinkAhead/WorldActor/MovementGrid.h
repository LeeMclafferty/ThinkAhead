// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovementGrid.generated.h"

USTRUCT(BlueprintType)
struct FTileInfo 
{
	GENERATED_USTRUCT_BODY()

	bool bisValidTile;
	int32 Row;
	int32 Column;

	FTileInfo()
		:bisValidTile(false), Row(0), Column(0)
	{

	}
};

UCLASS()
class THINKAHEAD_API AMovementGrid : public AActor
{
	GENERATED_BODY()
	
public:	
	AMovementGrid();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

private:	
	virtual void OnConstruction(const FTransform& Transform) override;

	class UProceduralMeshComponent* GridMesh;
};
