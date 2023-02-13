// Fill out your copyright notice in the Description page of Project Settings.


#include "ThinkAhead/Pawn/CameraPawn.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"

#include "ThinkAhead/WorldActor/ControlledCube.h"

ACameraPawn::ACameraPawn()
	:PlayersCube(nullptr)
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


void ACameraPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACameraPawn::SetPlayerCube(AControlledCube* NewCube)
{
	PlayersCube = NewCube;
}

