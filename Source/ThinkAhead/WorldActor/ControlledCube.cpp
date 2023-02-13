// Fill out your copyright notice in the Description page of Project Settings.


#include "ThinkAhead/WorldActor/ControlledCube.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"

#include "ThinkAhead/WorldActor/GridTile.h"
#include "ThinkAhead/WorldActor/Obstacle.h"

AControlledCube::AControlledCube()
	:CubeSpeed(10.f), CubeState(ECubeState::ECS_Idle)
{
	PrimaryActorTick.bCanEverTick = true;

	MovementBox = CreateDefaultSubobject<UBoxComponent>(TEXT("MovementBox"));
	SetRootComponent(MovementBox);
	
	CubeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CubeMesh"));
	CubeMesh->SetupAttachment(RootComponent);
}

void AControlledCube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CheckNextTile();
	SetCurrentTile();
	if (CubeState == ECubeState::ECS_Moving)
	{
		MoveForward();
	}
}

void AControlledCube::BeginPlay()
{
	Super::BeginPlay();
}

// Need to make this just a Move function and be able to pass in a world direction
void AControlledCube::MoveForward()
{
	FVector Target = GetActorLocation() += FVector(0.f, CubeSpeed, 0.f);
	SetActorLocation(FMath::Lerp(GetActorLocation(), Target, 1.f));
}

void AControlledCube::MoveRight()
{
	FVector Target = GetActorLocation() += FVector(CubeSpeed, 0.f, 0.f);
	SetActorLocation(FMath::Lerp(GetActorLocation(), Target, 1.f));
}

void AControlledCube::SetCurrentTile()
{
	FVector StartLocation = GetActorLocation();
	FVector EndLocation = GetActorLocation() - FVector(0.f, 0.f, 20.f);
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	FHitResult OutHit;

	//DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Red, false, 1.f, 0, 5.f);
	GetWorld()->LineTraceSingleByChannel(OutHit, StartLocation, EndLocation, ECC_GameTraceChannel2, Params);

	if (auto TileActor = Cast<AGridTile>(OutHit.GetActor()))
	{
		//GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Purple, FString::Printf(TEXT("Hit Detected")));
		if (TileActor == CurrentTile)
			return;
		CurrentTile = TileActor;
	}
}

void AControlledCube::CheckNextTile()
{
	FVector StartLocation = FVector(GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z + 50.f);
	FVector EndLocation = FVector(GetActorLocation().X, GetActorLocation().Y + 100.f, GetActorLocation().Z + 50.f);
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	FHitResult OutHit;

	//DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Red, false, 1.f, 0, 5.f);
	GetWorld()->LineTraceSingleByChannel(OutHit, StartLocation, EndLocation, ECC_GameTraceChannel1, Params);

	if (auto Obstacle = Cast<AObstacle>(OutHit.GetActor()))
	{
		CubeState = ECubeState::ECS_Idle;
		if(CurrentTile)
			SetActorLocation(CurrentTile->GetTileCenter());
	}
}

