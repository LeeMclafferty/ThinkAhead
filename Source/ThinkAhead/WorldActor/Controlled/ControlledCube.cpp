

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
#include "ThinkAhead/ActorComponet/DetectionComponent.h"

AControlledCube::AControlledCube()
	:CheckReach(100.f), bIsGameStarted(false), SnortSoundFrequency(10.f)
{
	PrimaryActorTick.bCanEverTick = true;

	MovementBox = CreateDefaultSubobject<UBoxComponent>(TEXT("MovementBox"));
	SetRootComponent(MovementBox);
	
	CubeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CubeMesh"));
	CubeMesh->SetupAttachment(RootComponent);

	SimpleMovementComponent = CreateDefaultSubobject<USimpleMovement>(TEXT("SimpleMovementComponent"));
	StateManager = CreateDefaultSubobject<UStateManager>(TEXT("StateManager"));
	DetectionComponent = CreateDefaultSubobject<UDetectionComponent>(TEXT("DetectionComponent"));
}

void AControlledCube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	FVector StartLocation = GetActorLocation();
	FVector EndLocation = GetActorLocation() - FVector(0.f, 0.f, 100.f);
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	FHitResult OutHit;

	//DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Red, false, 5.f, 0, 1.f);

	if (bIsGameStarted)
	{
		if (GetCubeState() != ECubeState::ECS_Idle)
		{
			CheckForObstacle();
			DetectionComponent->SetCurrentTile();
		}
		
		CheckState();

		if (!DetectionComponent->GetCurrentTile())
		{
			OnDeath();
		}
	}
	if (GetWorld()->TimeSince(SnortSoundTimer) > SnortSoundFrequency)
	{
		PlayRandomSnort();
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

	DetectionComponent->SetCurrentTile();
	SetActorLocation(DetectionComponent->GetCurrentTile()->GetTileCenter());
}

void AControlledCube::CheckForObstacle()
{

	FHitResult OutHitFront = DetectionComponent->TraceInFrontActor(ECC_GameTraceChannel1, SetTraceEndDirection());
	FHitResult OutHitUnder = DetectionComponent->TraceUnderActor(ECC_GameTraceChannel1);

	if (auto Front = Cast<AObstacle>(OutHitFront.GetActor()))
	{
		Front->PerformAction();
	}
	else if (auto Under = Cast<AObstacle>(OutHitUnder.GetActor()))
	{
		Under->PerformAction();
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

void AControlledCube::PlayRandomSnort()
{
	int32 Index = FMath::RandRange(0, SnortSounds.Num() - 1);
	USoundCue* Snort = SnortSounds[Index];
	SnortSoundTimer = GetWorld()->GetTimeSeconds();

	if (Snort)
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), (USoundBase*)Snort, GetActorLocation(), .3, 1.4);
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
	if (DeathMesh)
		CubeMesh->SetStaticMesh(DeathMesh);
	
	if(DeathVFX)
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), DeathVFX, GetActorLocation(), GetActorRotation(), FVector::OneVector);
	
	if (DeathSound)
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), (USoundBase*)DeathSound, GetActorLocation());
	
	SimpleMovementComponent->ClearMovesToMake();
	SetCubeState(ECubeState::ECS_Idle);
	
	CubeController->CreateLoseScreen();
}

