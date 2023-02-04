// Fill out your copyright notice in the Description page of Project Settings.


#include "ThinkAhead/WorldActor/MovementGrid.h"
#include "ProceduralMeshComponent.h"

AMovementGrid::AMovementGrid()
	:Width(4), Height(4), Spacing(50.f), bGenerateMesh(false)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GridMesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("GridMesh"));
	GridMesh->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
}

void AMovementGrid::BeginPlay()
{
	Super::BeginPlay();
	
}


void AMovementGrid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMovementGrid::ClearMeshData()
{
	Verticies.Empty();
	Triangles.Empty();
	Uvs.Empty();
	Normals.Empty();
	VertexColors.Empty();
	Tangents.Empty();
}

void AMovementGrid::GenerateVerticies()
{
	float UvSpacing = 1.f / FMath::Max(Height, Width);

	for (int32 y = 0; y < Height; y++)
	{
		for (int32 x = 0; x < Width; x++)
		{
			Verticies.Add(FVector(x * Spacing, y * Spacing, 0));
			Normals.Add(FVector(0.f, 0.f, 1.f));
			Uvs.Add(FVector2D(x * UvSpacing, y * UvSpacing));
			VertexColors.Add(FLinearColor(0.f, 0.f, 0.f, 1.f));
			Tangents.Add(FProcMeshTangent(1.0f, 0.f, 0.f));
		}
	}
}

void AMovementGrid::GenerateTriangles()
{
	for (int32 y = 0; y < Height - 1; y++)
	{
		for (int32 x = 0; x < Width - 1; x++)
		{
			Triangles.Add(x + (y * Width));
			Triangles.Add(x + (y * Width) + Width);
			Triangles.Add(x + (y * Width) + Width + 1);

			Triangles.Add(x + (y * Width));
			Triangles.Add(x + (y * Width) + Width + 1);
			Triangles.Add(x + (y * Width) + 1);
		}
	}
}

void AMovementGrid::OnConstruction(const FTransform& Transform)
{
	ClearMeshData();

	if (bGenerateMesh)
	{
		bGenerateMesh = false;
		ClearMeshData();
		GenerateVerticies();
		GenerateTriangles();
	}
	GridMesh->CreateMeshSection_LinearColor(0, Verticies, Triangles, Normals, Uvs, VertexColors, Tangents, false);
}

