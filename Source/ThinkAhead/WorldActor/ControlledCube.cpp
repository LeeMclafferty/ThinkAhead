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

AControlledCube::AControlledCube()
	:CubeSpeed(10.f), CubeState(ECubeState::ECS_None), CheckReach(100.f), bIsGameStarted(false)
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

	UE_LOG(LogTemp, Warning, TEXT("CubeSpeed: %f"), CubeSpeed);

	if (bIsGameStarted)
	{
		if (CubeState != ECubeState::ECS_Idle)
		{
			SetCurrentTile();
			CheckNextTile();
		}
		CheckState();
	}
}

void AControlledCube::AddMoveToMake(class UMovePiece* AddMove)
{
	if (AddMove)
		MovesToMake.Add(AddMove);
}

void AControlledCube::SetCurrentMove(class UMovePiece* NewCurrent)
{
	CurrentMove = NewCurrent;
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

// Need to make this just a Move function and be able to pass in a world direction
void AControlledCube::MoveNorth()
{
	FVector Target = GetActorLocation() += FVector(0.f, CubeSpeed, 0.f);
	SetActorLocation(FMath::Lerp(GetActorLocation(), Target, 1.f));
}

void AControlledCube::MoveWest()
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
	FVector EndLocation = SetTraceEndLocation();
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	FHitResult OutHit;

	//DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Red, false, .2f, 0, 5.f);
	GetWorld()->LineTraceSingleByChannel(OutHit, StartLocation, EndLocation, ECC_GameTraceChannel1, Params);

	if (auto Obstacle = Cast<AObstacle>(OutHit.GetActor()))
	{
		CubeState = ECubeState::ECS_Idle;
		if(CurrentTile)
			SetActorLocation(CurrentTile->GetTileCenter());
	}
}

FVector AControlledCube::SetTraceEndLocation()
{
	if (CubeState == ECubeState::ECS_MovingNorthSouth)
	{
		if (FMath::Sign(CubeSpeed) == 1)
		{
			return FVector(GetActorLocation().X, GetActorLocation().Y + 100.f, GetActorLocation().Z + 50.f);
		}
		else
		{
			return FVector(GetActorLocation().X, GetActorLocation().Y - CheckReach, GetActorLocation().Z + 50.f);
		}
	}
	else if (CubeState == ECubeState::ECS_MoveingEastWest)
	{
		if (FMath::Sign(CubeSpeed) == 1)
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

	if (CubeState == ECubeState::ECS_None)
	{
		MovesToMake[0]->Move();
	}
	else if (CubeState == ECubeState::ECS_Idle)
	{
		for (auto Move : MovesToMake)
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
	else if (CubeState == ECubeState::ECS_MovingNorthSouth)
	{
		MoveNorth();
	}
	else if (CubeState == ECubeState::ECS_MoveingEastWest)
	{
		MoveWest();
	}

}

void AControlledCube::LookNorth()
{
	FRotator CurrentRotation = GetActorRotation();
	CurrentRotation.Yaw = 0.f;
	SetActorRotation(CurrentRotation);
}

void AControlledCube::LookWest()
{
	FRotator CurrentRotation = GetActorRotation();
	CurrentRotation.Yaw = -90.f;
	SetActorRotation(CurrentRotation);
}

void AControlledCube::LookSouth()
{
	FRotator CurrentRotation = GetActorRotation();
	CurrentRotation.Yaw = 180.f;
	SetActorRotation(CurrentRotation);
}

void AControlledCube::LookEast()
{
	FRotator CurrentRotation = GetActorRotation();
	CurrentRotation.Yaw = 90.f;
	SetActorRotation(CurrentRotation);
}

