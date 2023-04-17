// Copyright © 2023 Lee Mclafferty. All rights reserved. This code is the property of Lee Mclafferty and may not be used for resale, redistribution, or for the purpose of making a profit without written consent from the owner.


#include "ThinkAhead/Pawn/CameraPawn.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "Kismet/GameplayStatics.h"

#include "ThinkAhead/ThinkAheadGameModeBase.h"
#include "ThinkAhead/WorldActor/Controlled/ControlledCube.h"
#include "ThinkAhead/GameInstance/ThinkAheadGameInstance.h"

ACameraPawn::ACameraPawn()
: ZoomInLimit(500.f), ZoomOutLimit(3000.f), OrthoFOV(25.f), PerspectiveFOV(90.f), OrthZoomLimit(9000.f), PerspectiveZoomLimit(3000.f), PlayersCube(nullptr)
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

	GameInstance = Cast<UThinkAheadGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
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

void ACameraPawn::CheckOrtho()
{
	ChangePerspctive();
	SwapZoomOutLimit();
}

void ACameraPawn::SwapZoomOutLimit()
{
	if (!GameInstance)
		return;

	ZoomOutLimit = (!GameInstance->IsOrtho()) ? PerspectiveZoomLimit : OrthZoomLimit;
	SpringArm->TargetArmLength = ZoomOutLimit;
}

void ACameraPawn::ChangePerspctive()
{
	if (!GameInstance)
		return;

	GameCamera->FieldOfView = (!GameInstance->IsOrtho()) ? PerspectiveFOV : OrthoFOV;
}



