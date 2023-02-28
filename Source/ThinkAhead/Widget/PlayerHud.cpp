// Fill out your copyright notice in the Description page of Project Settings.


#include "ThinkAhead/Widget/PlayerHud.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"

#include "ThinkAhead/Pawn/CameraPawn.h"
#include "ThinkAhead/WorldActor/ControlledCube.h"


void UPlayerHud::NativeConstruct()
{
	Super::NativeConstruct();

	if (ACameraPawn* PP = Cast<ACameraPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0)))
	{
		PlayerPawn = PP;
	}
}

// void UPlayerHud::MoveNorth()
// {
// 	if (!PlayerPawn)
// 		return;
// 
// 	UE_LOG(LogTemp, Error, TEXT("MopeForward"));\
// 	PlayerPawn->GetPlayerCube()->CubeSpeed = 20;
// 	PlayerPawn->GetPlayerCube()->SetCubeState(ECubeState::ECS_Moving);
// }
// 
// void UPlayerHud::MoveSouth()
// {
// 	if (!PlayerPawn)
// 		return;
// 
// 	PlayerPawn->GetPlayerCube()->CubeSpeed = -20;
// 	PlayerPawn->GetPlayerCube()->SetCubeState(ECubeState::ECS_Moving);
// }
// 
// void UPlayerHud::MoveLeft()
// {
// 	if (!PlayerPawn)
// 		return;
// 
// 	PlayerPawn->GetPlayerCube()->CubeSpeed = -20;
// 	PlayerPawn->GetPlayerCube()->SetCubeState(ECubeState::ECS_Moving);
// }
// 
// void UPlayerHud::MoveRight()
// {
// 	if (!PlayerPawn)
// 		return;
// 
// 	PlayerPawn->GetPlayerCube()->CubeSpeed = 20;
// 	PlayerPawn->GetPlayerCube()->SetCubeState(ECubeState::ECS_Moving);

 
