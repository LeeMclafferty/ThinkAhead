// Fill out your copyright notice in the Description page of Project Settings.


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
	:TileSize(125), TileType(ETileType::ETT_None), Width(TileSize), Height(TileSize)
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
	ClearTileActor();
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
		case ETileType::ETT_None:
			ClearTileActor();
			break;
		case ETileType::ETT_Start:
			SpawnPlayerCube();
			break;
		case ETileType::ETT_StopCube:
			SpawnActor(StopCubeClass);
			break;
		case ETileType::ETT_KillTile:
			SpawnActor(KillTileClass);
			break;
		case ETileType::ETT_WinTile:
			SpawnActor(WinLevelClass);
			break;
		case ETileType::ETT_ChangeNorth:
			SpawnActor(ChangeNorthClass);
			break;
		case ETileType::ETT_ChangeSouth:
			SpawnActor(ChangeSouthClass);
			break;
		case ETileType::ETT_ChangeEast:
			SpawnActor(ChangeEastClass);
			break;
		case ETileType::ETT_ChangeWest:
			SpawnActor(ChangeWestClass);
			break;
		case ETileType::ETT_Button:
			SpawnActor(ButtonTriggerClass);
		default:
			break;
	}
}

void AGridTile::SpawnPlayerCube()
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

	TileSpawnedActor = PlayerCube;
}

void AGridTile::ClearTileActor()
{
	if (TileSpawnedActor)
	{
		TileSpawnedActor->Destroy();
		TileSpawnedActor = nullptr;
	}
}

void AGridTile::SetPlayerPawnRef()
{
	if (auto Player = Cast<ACameraPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0)))
	{
		PlayerPawn = Player;
	}
}

void AGridTile::SpawnActor(TSubclassOf<AActor> ActorClass)
{
	if (!ActorClass)
		return;

	FVector Location = GetTileCenter();
	FRotator Rotation = FRotator::ZeroRotator;
	FVector Scale = FVector::OneVector;
	FTransform SpawnTransform = FTransform(Rotation, Location, Scale);
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;

	TileSpawnedActor = GetWorld()->SpawnActor<AActor>(ActorClass, SpawnTransform, SpawnParams);
}

