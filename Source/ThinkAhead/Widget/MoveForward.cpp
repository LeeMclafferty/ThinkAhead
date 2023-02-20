// Fill out your copyright notice in the Description page of Project Settings.


#include "ThinkAhead/Widget/MoveForward.h"
#include "Kismet/Gameplaystatics.h"

#include "ThinkAhead/Pawn/CameraPawn.h"
#include "ThinkAhead/WorldActor/ControlledCube.h"

void UMoveForward::NativeConstruct()
{
	Super::NativeConstruct();


}

void UMoveForward::Move()
{
	Super::Move();

	if (!PlayerPawn)
		return;

	UE_LOG(LogTemp, Error, TEXT("MoveForward"));
	PlayerPawn->GetPlayerCube()->CubeSpeed = 20;
	PlayerPawn->GetPlayerCube()->SetCubeState(ECubeState::ECS_Moving);

}
