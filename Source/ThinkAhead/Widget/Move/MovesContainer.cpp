// Fill out your copyright notice in the Description page of Project Settings.


#include "ThinkAhead/Widget/Move/MovesContainer.h"
#include "Components/Image.h"
#include "Components/HorizontalBox.h"
#include "Blueprint/DragDropOperation.h"
#include "Kismet/GameplayStatics.h"
#include "Components/PanelWidget.h"
#include "Components/Border.h"

#include "ThinkAhead/Widget/GamePiece/MovePiece.h"
#include "ThinkAhead/Widget/Move/SinglePieceContainer.h"
#include "ThinkAhead/ThinkAheadGameModeBase.h"

void UMovesContainer::NativeConstruct()
{
	Super::NativeConstruct();


	AThinkAheadGameModeBase* Gm = Cast<AThinkAheadGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	ConstructMoveToContainer(Gm);
	ConstructMoveFromContainer(Gm);



}

bool UMovesContainer::NativeOnDrop(const FGeometry& InGeomtry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	bool Handled = Super::NativeOnDrop(InGeomtry, InDragDropEvent, InOperation);

	if (!InOperation)
		return false;

	UMovePiece* MovePiecePayload = Cast<UMovePiece>(InOperation->Payload);

	if (!MovePiecePayload)
		return false;


	return AddMovePiece(MovePiecePayload);
}

bool UMovesContainer::AddMovePiece(class UMovePiece* ToAdd)
{
	
	for (int i = 0; i < MovesPanelBox->GetChildrenCount(); i++)
	{
		USinglePieceContainer* CurrChild = Cast<USinglePieceContainer>(MovesPanelBox->GetChildAt(i));

		if (!CurrChild)
			return false;

		if (!CurrChild->bHasPiece)
		{
			CurrChild->HoldPiece(ToAdd);
			return true;
		}

	}

	return false;
}

void UMovesContainer::ConstructMoveFromContainer(class AThinkAheadGameModeBase* GameMode)
{
	if (ContainerType != EContainerType::ECT_MoveFrom || !GameMode)
		return;

	ContainerSize = GameMode->GetNumMoveOptions();

	if (PieceContatinerClass)
	{
		for (int32 i = 0; i < ContainerSize; i++)
		{
			USinglePieceContainer* CurrContainer = CreateWidget<USinglePieceContainer>(this, PieceContatinerClass);
			MovesPanelBox->AddChild(CurrContainer);

			CurrContainer->HoldPiece(GameMode->GetStartingPieces()[i]);
		}
	}
}

void UMovesContainer::ConstructMoveToContainer(class AThinkAheadGameModeBase* GameMode)
{
	if (ContainerType != EContainerType::ECT_MoveTo || !GameMode)
		return;
	
	ContainerSize = GameMode->GetNumMovestoMake();

	if (PieceContatinerClass)
	{
		for (int32 i = 0; i < ContainerSize; i++)
		{
			USinglePieceContainer* CurrContainer = CreateWidget<USinglePieceContainer>(this, PieceContatinerClass);
			MovesPanelBox->AddChild(CurrContainer);
		}
	}
}

