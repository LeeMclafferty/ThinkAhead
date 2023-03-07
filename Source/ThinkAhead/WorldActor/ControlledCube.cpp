// Fill out your copyright notice in the Description page of Project Settings.


#include "ThinkAhead/WorldActor/ControlledCube.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

#include "ThinkAhead/WorldActor/GridTile.h"
#include "ThinkAhead/WorldActor/Obstacle.h"
#include "ThinkAhead/Widget/MovePiece.h"
#include "ThinkAhead/Controller/CubeController.h"
#include "ThinkAhead/Widget/ExecuteMoves.h"
#include "ThinkAhead/ActorComponet/SimpleMovement.h"

AControlledCube::AControlledCube()
	:CheckReach(100.f), bIsGameStarted(false)
{
	PrimaryActorTick.bCanEverTick = true;

	MovementBox = CreateDefaultSubobject<UBoxComponent>(TEXT("MovementBox"));
	SetRootComponent(MovementBox);
	
	CubeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CubeMesh"));
	CubeMesh->SetupAttachment(RootComponent);

	SimpleMovementComponent = CreateDefaultSubobject<USimpleMovement>(TEXT("SimpleMovementComponent"));
	StateManager = CreateDefaultSubobject<UStateManager>(TEXT("StateManager"));
}

void AControlledCube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsGameStarted)
	{
		if (GetCubeState() != ECubeState::ECS_Idle)
		{
			SetCurrentTile();
			CheckNextTile();
		}
		CheckState();
	}
}

void AControlledCube::BeginPlay()
{
	Super::BeginPlay();

	CubeController = Cast<ACubeController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	
	if (CubeController)
	{
		CubeController->SetControlledCube(this);
	}
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
	FVector EndLocation = SetTraceEndLocation();
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	FHitResult OutHit;

	//DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Red, false, .2f, 0, 5.f);
	GetWorld()->LineTraceSingleByChannel(OutHit, StartLocation, EndLocation, ECC_GameTraceChannel1, Params);

	if (auto Obstacle = Cast<AObstacle>(OutHit.GetActor()))
	{
		SetCubeState(ECubeState::ECS_Idle);
		if(CurrentTile)
			SetActorLocation(CurrentTile->GetTileCenter());
	}
}

FVector AControlledCube::SetTraceEndLocation()
{
	if (GetCubeState() == ECubeState::ECS_MovingNorthSouth)
	{
		if (FMath::Sign(SimpleMovementComponent->GetCubeSpeed()) == 1)
		{
			return FVector(GetActorLocation().X, GetActorLocation().Y + 100.f, GetActorLocation().Z + 50.f);
		}
		else
		{
			return FVector(GetActorLocation().X, GetActorLocation().Y - CheckReach, GetActorLocation().Z + 50.f);
		}
	}
	else if (GetCubeState() == ECubeState::ECS_MoveingEastWest)
	{
		if (FMath::Sign(SimpleMovementComponent->GetCubeSpeed()) == 1)
		{
			return FVector(GetActorLocation().X + CheckReach, GetActorLocation().Y, GetActorLocation().Z + 50.f);
		}
		else
		{
			return FVector(GetActorLocation().X - CheckReach, GetActorLocation().Y, GetActorLocation().Z + 50.f);
		}
	}

	return FVector::ZeroVector;
}

void AControlledCube::CheckState()
{
	if (!CubeController)
	{
		CubeController = Cast<ACubeController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
		CubeController->SetControlledCube(this);
	}

	if (GetCubeState() == ECubeState::ECS_None)
	{
		SimpleMovementComponent->GetMovesToMake()[0]->Move();
	}
	else if (GetCubeState() == ECubeState::ECS_Idle)
	{
		for (auto Move : SimpleMovementComponent->GetMovesToMake())
		{
			if (Move->HasActivated())
			{
				continue;
			}
			else
			{
				Move->Move();
				break;
			}
		}
	}
	else if (GetCubeState() == ECubeState::ECS_MovingNorthSouth)
	{
		SimpleMovementComponent->MoveNorth();
	}
	else if (GetCubeState() == ECubeState::ECS_MoveingEastWest)
	{
		SimpleMovementComponent->MoveWest();
	}

}

ECubeState AControlledCube::GetCubeState()
{
	if (!StateManager)
		return ECubeState::ECS_None;

	return StateManager->GetState();
}

void AControlledCube::SetCubeState(ECubeState NewState)
{
	if (!StateManager)
		return;

	StateManager->SetState(NewState);
}

