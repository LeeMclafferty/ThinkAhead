// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovementGrid.generated.h"

UCLASS()
class THINKAHEAD_API AMovementGrid : public AActor
{
	GENERATED_BODY()
	
public:	
	AMovementGrid();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY()
	TArray<FVector> Verticies;
	UPROPERTY()
	TArray<int32> Triangles;
	UPROPERTY()
	TArray<FVector> Normals;
	UPROPERTY()
	TArray<FVector2D> Uvs;
	UPROPERTY()
	TArray<FLinearColor> VertexColors;
	UPROPERTY()
	TArray<struct FProcMeshTangent> Tangents;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ProceduralMesh")
	int32 Height;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ProceduralMesh")
	int32 Width;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ProceduralMesh")
	float Spacing;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ProceduralMesh")
	bool bGenerateMesh;

private:	
	UPROPERTY(VisibleAnywhere)
	class UProceduralMeshComponent* GridMesh;

	virtual void OnConstruction(const FTransform& Transform) override;

	void ClearMeshData();
	void GenerateVerticies();
	void GenerateTriangles();



};
