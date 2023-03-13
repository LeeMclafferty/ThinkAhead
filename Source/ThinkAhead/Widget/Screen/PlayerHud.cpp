// Fill out your copyright notice in the Description page of Project Settings.


#include "ThinkAhead/Widget/Screen/PlayerHud.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"

#include "ThinkAhead/Pawn/CameraPawn.h"
#include "ThinkAhead/WorldActor/Controlled/ControlledCube.h"
#include "ThinkAhead/Widget/Move/MovesContainer.h"
#include "ThinkAhead/Widget/Move/MoveToContainer.h"


void UPlayerHud::NativeConstruct()
{
	Super::NativeConstruct();

	if (ACameraPawn* PP = Cast<ACameraPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0)))
	{
		PlayerPawn = PP;
	}

	ExecuteButton = MoveToPanel->GetExecuteButton();
}


 
