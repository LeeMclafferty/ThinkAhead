// Fill out your copyright notice in the Description page of Project Settings.


#include "ThinkAhead/Widget/ExecuteMoves.h"
#include "Components/PanelWidget.h"
#include "Kismet/GameplayStatics.h"

#include "ThinkAhead/Widget/MovesContainer.h"
#include "ThinkAhead/Widget/SinglePieceContainer.h"
#include "ThinkAhead/Widget/MovePiece.h"
#include "ThinkAhead/WorldActor/ControlledCube.h"
#include "ThinkAhead/Pawn/CameraPawn.h"

void UExecuteMoves::NativeConstruct()
{
	Super::NativeConstruct();

	PlayerPawn = Cast<ACameraPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
}

void UExecuteMoves::Execute()
{
	UMovesContainer* OwningContainer = Cast<UMovesContainer>(GetParent()->GetOuter()->GetOuter());

	if (!OwningContainer)
		return;

	UPanelWidget* ContainingBox = OwningContainer->GetMovesPanelBox();

	if (!ContainingBox)
		return;
	
	/* TODO: Execute the move, once cube is idle, execute next move. */
	for (int i = 0; i < ContainingBox->GetChildrenCount(); i++)
	{
		USinglePieceContainer* SingleContainer = Cast<USinglePieceContainer>(ContainingBox->GetChildAt(i));
		if (!SingleContainer || !PlayerPawn)
			break;

		UMovePiece* CurrentMove = SingleContainer->GetHeldPiece();

		if (!CurrentMove)
			break;

		if (PlayerPawn->GetPlayerCube())
		{
			PlayerPawn->GetPlayerCube()->AddMoveToMake(CurrentMove);
		}

		PlayerPawn->GetPlayerCube()->SetCurrentMove(PlayerPawn->GetPlayerCube()->GetMovesToMake()[0]);
	}
}
