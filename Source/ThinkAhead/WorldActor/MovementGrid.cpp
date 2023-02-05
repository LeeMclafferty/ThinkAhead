// Fill out your copyright notice in the Description page of Project Settings.


#include "ThinkAhead/WorldActor/MovementGrid.h"
#include "ProceduralMeshComponent.h"

AMovementGrid::AMovementGrid()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GridMesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("GridMesh"));
	GridMesh->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
}

void AMovementGrid::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	

}

void AMovementGrid::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMovementGrid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


