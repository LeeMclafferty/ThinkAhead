// Fill out your copyright notice in the Description page of Project Settings.


#include "ThinkAhead/Widget/PlayerHud.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"

#include "ThinkAhead/Pawn/CameraPawn.h"
#include "ThinkAhead/WorldActor/ControlledCube.h"
#include "ThinkAhead/Widget/MovesContainer.h"
#include "ThinkAhead/Widget/MoveToContainer.h"


void UPlayerHud::NativeConstruct()
{
	Super::NativeConstruct();

	if (ACameraPawn* PP = Cast<ACameraPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0)))
	{
		PlayerPawn = PP;
	}

	ExecuteButton = MoveToPanel->GetExecuteButton();
}


 
