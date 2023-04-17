// Copyright © 2023 Lee Mclafferty. All rights reserved. This code is the property of Lee Mclafferty and may not be used for resale, redistribution, or for the purpose of making a profit without written consent from the owner.


#include "ThinkAhead/WorldActor/Grid/GridTile.h"
#include "ProceduralMeshComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"

#include "ThinkAhead/ThinkAheadGameModeBase.h"
#include "ThinkAhead/WorldActor/Controlled/ControlledCube.h"
#include "ThinkAhead/Pawn/CameraPawn.h"
#include "ThinkAhead/WorldActor/Obstacle/StopCube.h"
#include "ThinkAhead/WorldActor/Obstacle/KillSpace.h"
#include "ThinkAhead/WorldActor/Obstacle/LevelWin.h"
#include "ThinkAhead/WorldActor/Obstacle/ChangeDirection.h"
#include "ThinkAhead/WorldActor/Obstacle/ButtonTrigger.h"

// Sets default values
AGridTile::AGridTile()
	:TileSize(125), Width(TileSize), Height(TileSize)
{
	PrimaryActorTick.bCanEverTick = true;

	TileMesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("TileMesh"));
	
	TileMesh->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
	TileMesh->SetCollisionProfileName(FName("Tile"));
	SetRootComponent(TileMesh);
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

	TArray<FVector> VertsBuffer;
	TArray<int32> TrisBuffer;

	GenerateTileVerts(VertsBuffer);
	GenerateTrianles(TrisBuffer);
 	Verticies = VertsBuffer;
 	Triangles = TrisBuffer;

	TileMesh->CreateMeshSection_LinearColor(0, Verticies, Triangles, Normals, Uvs, VertexColors, Tangents, true);
}

void AGridTile::BeginPlay()
{
	Super::BeginPlay();

// 	SetPlayerPawnRef();
// 	HandleSpawning();
}

// Called every frame
void AGridTile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

FVector AGridTile::GetTileCenter()
{
	float AvgX = 0;
	float AvgY = 0;

	float SumX = 0;
	float SumY = 0;

	for (auto i : Verticies)
	{
		SumX += i.X;
		SumY += i.Y;
	}

	AvgX = (SumX / Verticies.Num());
	AvgY = (SumY / Verticies.Num());
	FVector CenterVector(AvgX, AvgY, TileMesh->GetComponentLocation().Z + 5.f);

	return UKismetMathLibrary::TransformLocation(GetActorTransform(), CenterVector);
}

void AGridTile::SetTileColor(class UMaterialInterface* Material)
{
	if (TileMesh)
	{
		TileMesh->SetMaterial(0, Material);
	}
}

void AGridTile::DestroyTile()
{
	Destroy();
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

