// Fill out your copyright notice in the Description page of Project Settings.


#include "ThinkAhead/Pawn/CameraPawn.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"

#include "ThinkAhead/WorldActor/Controlled/ControlledCube.h"

ACameraPawn::ACameraPawn()
	: ZoomInLimit(500.f), ZoomOutLimit(14000.f), PlayersCube(nullptr)
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

