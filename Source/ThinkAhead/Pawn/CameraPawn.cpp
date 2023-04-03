// Fill out your copyright notice in the Description page of Project Settings.


#include "ThinkAhead/Pawn/CameraPawn.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "Kismet/GameplayStatics.h"

#include "ThinkAhead/ThinkAheadGameModeBase.h"
#include "ThinkAhead/WorldActor/Controlled/ControlledCube.h"

ACameraPawn::ACameraPawn()
	: ZoomInLimit(500.f), ZoomOutLimit(14000.f), OrthoZoom(9000.f), PerspectiveZoom(3000.f), PlayersCube(nullptr)
{
	PrimaryActorTick.bCanEverTick = true;

	RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	GameCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("GameCamera"));

	SetRootComponent(RootComp);
	SpringArm->SetupAttachment(RootComp);
	GameCamera->SetupAttachment(SpringArm);
}

void ACameraPawn::BeginPlay()
{
	Super::BeginPlay();
	CheckOrtho();
}


void ACameraPawn::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (PlayerInputComponent)
	{
		PlayerInputComponent->BindAction("ZoomIn", IE_Pressed, this, &ACameraPawn::ZoomIn);
		PlayerInputComponent->BindAction("ZoomOut", IE_Pressed, this, &ACameraPawn::ZoomOut);
	}
}

void ACameraPawn::ZoomIn()
{
	if (SpringArm->TargetArmLength > ZoomInLimit)
	{
		SpringArm->TargetArmLength -= 200.f;
	}
	else
	{
		SpringArm->TargetArmLength = ZoomInLimit;
	}
}

void ACameraPawn::ZoomOut()
{
	if (SpringArm->TargetArmLength < ZoomOutLimit)
	{
		SpringArm->TargetArmLength += 200.f;
	}
	else
	{
		SpringArm->TargetArmLength = ZoomOutLimit;
	}
}


void ACameraPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACameraPawn::SetPlayerCube(AControlledCube* NewCube)
{
	PlayersCube = NewCube;
}

void ACameraPawn::SwapZoomOutLimit()
{
	ZoomOutLimit = (ZoomOutLimit == PerspectiveZoom) ? OrthoZoom : PerspectiveZoom;

	GetWorldTimerManager().SetTimer(ZoomHandle, this, &ACameraPawn::LerpToMaxZoom, 0.05f, true, 0.f);
}

void ACameraPawn::LerpToMaxZoom()
{
	float NewTargetArmLength = FMath::Lerp(SpringArm->TargetArmLength, ZoomOutLimit, .5f);
	if (!FMath::IsNearlyEqual(SpringArm->TargetArmLength, ZoomOutLimit, 1.f))
	{
		SpringArm->TargetArmLength = NewTargetArmLength;
	}
	else
	{
		GetWorldTimerManager().ClearTimer(ZoomHandle);
		SpringArm->TargetArmLength = ZoomOutLimit;
	}
}


void ACameraPawn::CheckOrtho()
{
	auto Gamemode = Cast<AThinkAheadGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	if (!Gamemode)
		return;

	//ChangePerspecive will swap the FOV, so I set it to the opposite of what I want here.
	if (Gamemode->IsOrtho())
	{
		GameCamera->FieldOfView = 90;
		ChangePerspctive();
		SwapZoomOutLimit();
	}
}

void ACameraPawn::ChangePerspctive()
{
	float Target = GameCamera->FieldOfView;
	Target = (Target == 90.f) ? 25.f : 90.f;

	if (Target == 90.f)
	{
		ZoomOutLimit = 3000.f;
	}
	else
	{
		ZoomOutLimit = 9000.f;
	}
	SpringArm->TargetArmLength = ZoomOutLimit;

	GetWorldTimerManager().SetTimer(TransitionHandle, [this, Target]()
		{
			UpdateFOV(Target);
		}, .05f, true, 0.0f);
}

void ACameraPawn::UpdateFOV(float NewFov)
{
	TargetFov = NewFov;

	float CurrentFov = FMath::Lerp(GameCamera->FieldOfView, TargetFov, .5f);
	if (!FMath::IsNearlyEqual(TargetFov, CurrentFov, 1.f))
	{
		GameCamera->SetFieldOfView(CurrentFov);
	}
	else
	{
		GetWorldTimerManager().ClearTimer(TransitionHandle);
		GameCamera->SetFieldOfView(TargetFov);
		//SwapZoomOutLimit();
	}
}


