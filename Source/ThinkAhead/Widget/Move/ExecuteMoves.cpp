// Fill out your copyright notice in the Description page of Project Settings.


#include "ThinkAhead/Widget/Move/ExecuteMoves.h"
#include "Components/PanelWidget.h"
#include "Kismet/GameplayStatics.h"

#include "ThinkAhead/Widget/Move/MovesContainer.h"
#include "ThinkAhead/Widget/Move/SinglePieceContainer.h"
#include "ThinkAhead/Widget/GamePiece/MovePiece.h"
#include "ThinkAhead/WorldActor/Controlled/ControlledCube.h"
#include "ThinkAhead/Pawn/CameraPawn.h"
#include "ThinkAhead/ActorComponet/SimpleMovement.h"

void UExecuteMoves::NativeConstruct()
{
	Super::NativeConstruct();

	PlayerPawn = Cast<ACameraPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
}

void UExecuteMoves::Execute()
{
	UMovesContainer* OwningContainer = Cast<UMovesContainer>(GetParent()->GetOuter()->GetOuter());

	if (!OwningContainer || PlayerPawn->GetPlayerCube()->IsGameStarted())
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
			PlayerPawn->GetPlayerCube()->GetSimpleMovementComp()->AddMoveToMake(CurrentMove);
		}

		PlayerPawn->GetPlayerCube()->GetSimpleMovementComp()->SetCurrentMove(PlayerPawn->GetPlayerCube()->GetSimpleMovementComp()->GetMovesToMake()[0]);
	}

	OnExecute.Broadcast();

}
