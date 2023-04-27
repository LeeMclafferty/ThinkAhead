// Copyright � 2023 Lee Mclafferty. All rights reserved. This code is the property of Lee Mclafferty and may not be used for resale, redistribution, or for the purpose of making a profit without written consent from the owner.


#include "ThinkAhead/Widget/Move/ExecuteMoves.h"
#include "Components/PanelWidget.h"
#include "Kismet/GameplayStatics.h"

#include "ThinkAhead/Widget/Move/MovesContainer.h"
#include "ThinkAhead/Widget/Move/SinglePieceContainer.h"
#include "ThinkAhead/Widget/GamePiece/MovePiece.h"
#include "ThinkAhead/WorldActor/Controlled/ControlledCube.h"
#include "ThinkAhead/Pawn/CameraPawn.h"
#include "ThinkAhead/ActorComponet/SimpleMovement.h"
#include "ThinkAhead/Controller/CubeController.h"

void UExecuteMoves::NativeConstruct()
{
	Super::NativeConstruct();

	PlayerController = Cast<ACubeController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
}

void UExecuteMoves::Execute()
{
	UMovesContainer* OwningContainer = Cast<UMovesContainer>(GetParent()->GetOuter()->GetOuter());

	if (!OwningContainer || PlayerController->GetControlledCube()->IsGameStarted())
		return;

	UPanelWidget* ContainingBox = OwningContainer->GetMovesPanelBox();

	if (!ContainingBox)
		return;

	if (ContainingBox->GetChildrenCount() < 1)
	{
		return;
	}

	for (int i = 0; i < ContainingBox->GetChildrenCount(); i++)
	{
		USinglePieceContainer* SingleContainer = Cast<USinglePieceContainer>(ContainingBox->GetChildAt(i));
		if (!SingleContainer || !PlayerController)
			break;
		UMovePiece* CurrentMove = SingleContainer->GetHeldPiece();

		if (!CurrentMove)
			break;
		
		OnExecute.Broadcast();
		if (PlayerController->GetControlledCube())
		{
			PlayerController->GetControlledCube()->GetSimpleMovementComp()->AddMoveToMake(CurrentMove);
		}

		PlayerController->GetControlledCube()->GetSimpleMovementComp()->SetCurrentMove(PlayerController->GetControlledCube()->GetSimpleMovementComp()->GetMovesToMake()[0]);
	}
}
