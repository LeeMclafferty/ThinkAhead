// Fill out your copyright notice in the Description page of Project Settings.


#include "ThinkAhead/WorldActor/Controlled/ControlledCube.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"

#include "ThinkAhead/WorldActor/Grid/GridTile.h"
#include "ThinkAhead/WorldActor/Obstacle/Obstacle.h"
#include "ThinkAhead/Widget/GamePiece/MovePiece.h"
#include "ThinkAhead/Controller/CubeController.h"
#include "ThinkAhead/Widget/Move/ExecuteMoves.h"
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
	
	FVector StartLocation = GetActorLocation();
	FVector EndLocation = GetActorLocation() - FVector(0.f, 0.f, 100.f);
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	FHitResult OutHit;

	DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Red, false, 5.f, 0, 1.f);

	if (bIsGameStarted)
	{
		if (GetCubeState() != ECubeState::ECS_Idle)
		{
			CheckForObstacle();
			SetCurrentTile();
		}
		
		CheckState();

		if (!CurrentTile)
		{
			OnDeath();
		}
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
	FHitResult OutHit = TraceUnderCube(ECC_GameTraceChannel2);

	if (auto TileActor = Cast<AGridTile>(OutHit.GetActor()))
	{
		if (TileActor == CurrentTile)
			return;

		CurrentTile = TileActor;
	}
}

FHitResult AControlledCube::TraceUnderCube(ECollisionChannel TraceChannel)
{
	FVector StartLocation = GetActorLocation();
	FVector EndLocation = GetActorLocation() - FVector(0.f, 0.f, 100.f);
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	FHitResult OutHit;

	GetWorld()->LineTraceSingleByChannel(OutHit, StartLocation, EndLocation, TraceChannel, Params);

	return OutHit;
}

FHitResult AControlledCube::TraceInFrontCube(ECollisionChannel TraceChannel)
{
	FVector StartLocation = FVector(GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z + 50.f);
	FVector EndLocation = SetTraceEndDirection();
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	FHitResult OutHit;

	GetWorld()->LineTraceSingleByChannel(OutHit, StartLocation, EndLocation, TraceChannel, Params);
	return OutHit;
}

void AControlledCube::CheckForObstacle()
{

	FHitResult OutHitFront = TraceInFrontCube(ECC_GameTraceChannel1);
	FHitResult OutHitUnder = TraceUnderCube(ECC_GameTraceChannel1);

	if (auto Front = Cast<AObstacle>(OutHitFront.GetActor()))
	{
		Front->PerformAction();
	}
	else if (auto Under = Cast<AObstacle>(OutHitUnder.GetActor()))
	{
		Under->PerformAction();
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, FString::Printf(TEXT("Hit")));
	}

}

FVector AControlledCube::SetTraceEndDirection()
{
	if (GetCubeState() == ECubeState::ECS_MovingNorthSouth)
	{
		if (SimpleMovementComponent->GetCubeSpeed() > 0.001f)
		{
			return FVector(GetActorLocation().X, GetActorLocation().Y + CheckReach, GetActorLocation().Z + 50.f);
		}
		else
		{
			return FVector(GetActorLocation().X, GetActorLocation().Y - CheckReach, GetActorLocation().Z + 50.f);
		}
	}
	else if (GetCubeState() == ECubeState::ECS_MoveingEastWest)
	{
		if (SimpleMovementComponent->GetCubeSpeed() > 0.001f)
		{
			return FVector(GetActorLocation().X + CheckReach, GetActorLocation().Y, GetActorLocation().Z + 50.f);
		}
		else
		{
			return FVector(GetActorLocation().X - CheckReach, GetActorLocation().Y, GetActorLocation().Z + 50.f);
		}
	}

	return GetActorLocation();
}


void AControlledCube::OnIdle()
{
	if (!SimpleMovementComponent || !StateManager)
		return;

	SimpleMovementComponent->SetMoveSpeed(0);
	StateManager->SetState(ECubeState::ECS_Idle);
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
		
		if (SimpleMovementComponent->GetMovesToMake().IsEmpty())
			return;

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

	if (NewState == ECubeState::ECS_Idle)
	{
		OnIdle();
	}
	else
	{
		StateManager->SetState(NewState);
	}
}

void AControlledCube::OnDeath()
{
	if (DeathMesh && DeathVFX)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), DeathVFX, GetActorLocation(), GetActorRotation(), FVector::OneVector);
		CubeMesh->SetStaticMesh(DeathMesh);
	}

	SetCubeState(ECubeState::ECS_Idle);
	CubeController->CreateLoseScreen();
}

