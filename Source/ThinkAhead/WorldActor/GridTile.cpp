// Fill out your copyright notice in the Description page of Project Settings.


#include "ThinkAhead/WorldActor/GridTile.h"
#include "ProceduralMeshComponent.h"

// Sets default values
AGridTile::AGridTile()
	:TileSize(100), Width(TileSize), Height(TileSize)
{
	PrimaryActorTick.bCanEverTick = true;

	TileMesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("TileMesh"));
	TileMesh->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);

}

void AGridTile::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	Width = TileSize;
	Height = TileSize;

	TArray<FVector> Normals;
	TArray<FVector2D> Uvs;
	TArray<FLinearColor> VertexColors;
	TArray<FProcMeshTangent> Tangents;
	
	TArray<FVector> Verticies;
	TArray<int32> Triangles;

	GenerateTileVerts(Verticies);
	GenerateTrianles(Triangles);

	TileMesh->CreateMeshSection_LinearColor(0, Verticies, Triangles, Normals, Uvs, VertexColors, Tangents, false);
}


void AGridTile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGridTile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGridTile::GenerateTileVerts(TArray<FVector>& Verts)
{
	Verts.Add(FVector(0, 0, 0));
	Verts.Add(FVector(Width, 0, 0));
	Verts.Add(FVector(Width, Height, 0));
	Verts.Add(FVector(0, Height, 0));
}

void AGridTile::GenerateTrianles(TArray<int32>& Tris)
{
	TArray<int32> Indicies;

	// Indicies are set up clockwise for the normals to be up in the Z.
	Indicies.Add(0);
	Indicies.Add(2);
	Indicies.Add(1);

	Indicies.Add(0);
	Indicies.Add(3);
	Indicies.Add(2);

	Tris.Append(Indicies);
}

