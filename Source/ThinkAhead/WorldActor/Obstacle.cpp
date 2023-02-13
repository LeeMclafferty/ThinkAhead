// Fill out your copyright notice in the Description page of Project Settings.


#include "ThinkAhead/WorldActor/Obstacle.h"
#include "Components/StaticMeshComponent.h"

AObstacle::AObstacle()
{
	PrimaryActorTick.bCanEverTick = true;

	ObstacleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ObstacleMesh"));
	ObstacleMesh->SetCollisionProfileName(FName("ECC_GameTraceChannel1"));

}

void AObstacle::BeginPlay()
{
	Super::BeginPlay();
	
}

void AObstacle::PerformAction()
{

}

void AObstacle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

