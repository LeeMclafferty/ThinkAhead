// Fill out your copyright notice in the Description page of Project Settings.


#include "ThinkAhead/WorldActor/Grid/MovementGrid.h"
#include "ProceduralMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"

#include "ThinkAhead/ThinkAheadGameModeBase.h"

AMovementGrid::AMovementGrid()
	:TileSize(125), NumRows(10), NumColumns(10), bGenerateNew(false), bClearGrid(false)
{
	PrimaryActorTick.bCanEverTick = true;

	Orgin = CreateDefaultSubobject<USphereComponent>(TEXT("Orgin"));
	SetRootComponent(Orgin);
}

AMovementGrid::~AMovementGrid()
{
	DestroyGrid();
}

void AMovementGrid::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	CreateNewGrid();

	if (bClearGrid)
	{
		bClearGrid = false;
		DestroyGrid();
	}
	
}


void AMovementGrid::BeginPlay()
{
	Super::BeginPlay();
}

void AMovementGrid::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	DestroyGrid();
}

void AMovementGrid::Destroyed()
{
	Super::Destroyed();
	DestroyGrid();
}

void AMovementGrid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMovementGrid::GenerateGrid()
{
	for (int32 x = 0; x < NumColumns; x++)
	{
		for (int32 y = 0; y < NumRows; y++)
		{
			FVector TileLocation = FVector(GetActorLocation().X + (x * TileSize), GetActorLocation().Y + (y * TileSize), GetActorLocation().Z);
			FTransform SpawnTransform(FRotator::ZeroRotator, TileLocation, FVector::OneVector);
			FActorSpawnParameters SpawnParameters;
			SpawnParameters.Owner = this;

			AGridTile* CurrentTile = GetWorld()->SpawnActor<AGridTile>(TileClass, SpawnTransform, SpawnParameters);

			if ((x + y) % 2)
			{
				CurrentTile->SetTileColor(FirstMaterial);
			}
			else 
			{
				CurrentTile->SetTileColor(SecondMaterial);
			}

			Tiles.Add(CurrentTile);
		}
	}
}

void AMovementGrid::DestroyGrid()
{
	for (int x = 0; x < Tiles.Num(); x++)
	{
		if(Tiles[x])
			Tiles[x]->DestroyTile();
	}
	Tiles.Empty();
}

void AMovementGrid::CreateNewGrid()
{
	DestroyGrid();
	bGenerateNew = false;
	GenerateGrid();
}

