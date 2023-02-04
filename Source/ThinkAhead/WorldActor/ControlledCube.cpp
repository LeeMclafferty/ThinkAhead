// Fill out your copyright notice in the Description page of Project Settings.


#include "ThinkAhead/WorldActor/ControlledCube.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AControlledCube::AControlledCube()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CubeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CubeMesh"));
}

// Called when the game starts or when spawned
void AControlledCube::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AControlledCube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

