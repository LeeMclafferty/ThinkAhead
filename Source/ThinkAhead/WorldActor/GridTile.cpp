// Fill out your copyright notice in the Description page of Project Settings.


#include "ThinkAhead/WorldActor/GridTile.h"
#include "ProceduralMeshComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"

#include "ThinkAhead/ThinkAheadGameModeBase.h"
#include "ThinkAhead/WorldActor/ControlledCube.h"
#include "ThinkAhead/Pawn/CameraPawn.h"
#include "ThinkAhead/WorldActor/StopCube.h"

// Sets default values
AGridTile::AGridTile()
	:TileSize(125), Width(TileSize), Height(TileSize)
{
	PrimaryActorTick.bCanEverTick = true;

	TileMesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("TileMesh"));
	
	TileMesh->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
	TileMesh->SetCollisionProfileName(FName("Tile"));

	TileType = ETileType::ETT_None;
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

	SetPlayerPawnRef();
	HandleSpawning();

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
	FVector CenterVector(AvgX, AvgY, TileMesh->GetComponentLocation().Z + 10.f);

	return UKismetMathLibrary::TransformLocation(GetActorTransform(), CenterVector);
}

void AGridTile::SetTileColor(class UMaterialInterface* Material)
{
	if (TileMesh)
	{
		TileMesh->SetMaterial(0, Material);
	}
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

void AGridTile::HandleSpawning()
{
	switch (TileType) 
	{
		case ETileType::ETT_Start:
			SpawnPlayersCube();
			break;
		case ETileType::ETT_StopCube:
			SpawnStopCube();
		default:
			break;
	}
}

void AGridTile::SpawnPlayersCube()
{
	FVector Location = GetTileCenter();
	FRotator Rotation = FRotator::ZeroRotator;
	FVector Scale = FVector::OneVector;
	FTransform SpawnTransform = FTransform(Rotation, Location, Scale);
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	auto PlayerCube = GetWorld()->SpawnActor<AControlledCube>(ControlledCubeClass, SpawnTransform, SpawnParams);
	if (PlayerPawn)
	{
		PlayerPawn->SetPlayerCube(PlayerCube);
	}
}

void AGridTile::SpawnStopCube()
{
	FVector Location = GetTileCenter();
	FRotator Rotation = FRotator::ZeroRotator;
	FVector Scale = FVector::OneVector;
	FTransform SpawnTransform = FTransform(Rotation, Location, Scale);
	FActorSpawnParameters SpawnParams;	
	SpawnParams.Owner = this;

	auto ObstacleCube = GetWorld()->SpawnActor<AStopCube>(StopCubeClass, SpawnTransform, SpawnParams);
}

void AGridTile::SetPlayerPawnRef()
{
	if (auto Player = Cast<ACameraPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0)))
	{
		PlayerPawn = Player;
	}
}

