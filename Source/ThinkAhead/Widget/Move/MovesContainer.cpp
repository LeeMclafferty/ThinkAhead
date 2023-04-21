// Copyright � 2023 Lee Mclafferty. All rights reserved. This code is the property of Lee Mclafferty and may not be used for resale, redistribution, or for the purpose of making a profit without written consent from the owner.


#include "ThinkAhead/Widget/Move/MovesContainer.h"
#include "Components/Image.h"
#include "Components/HorizontalBox.h"
#include "Blueprint/DragDropOperation.h"
#include "Kismet/GameplayStatics.h"
#include "Components/PanelWidget.h"
#include "Components/Border.h"
#include "Components/Button.h"

#include "ThinkAhead/Widget/GamePiece/MovePiece.h"
#include "ThinkAhead/Widget/Move/SinglePieceContainer.h"
#include "ThinkAhead/ThinkAheadGameModeBase.h"
#include "ThinkAhead/Gamemode/LevelGamemode.h"

void UMovesContainer::NativeConstruct()
{
	Super::NativeConstruct();

	ALevelGamemode* Gm = Cast<ALevelGamemode>(UGameplayStatics::GetGameMode(GetWorld()));

	ConstructMoveFromContainer(Gm);
	ConstructMoveToContainer(Gm);
}

bool UMovesContainer::NativeOnDrop(const FGeometry& InGeomtry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	bool Handled = Super::NativeOnDrop(InGeomtry, InDragDropEvent, InOperation);

	if (!InOperation)
		return false;

	UMovePiece* MovePiecePayload = Cast<UMovePiece>(InOperation->Payload);

	if (!MovePiecePayload)
		return false;

	MovePiecePayload->GetActionImage()->SetVisibility(ESlateVisibility::Visible);
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
			if(DropSound)
				UGameplayStatics::PlaySound2D(GetWorld(), (USoundBase*)DropSound);

			return true;
		}
	}

	return false;
}

void UMovesContainer::ConstructMoveFromContainer(class ALevelGamemode* GameMode)
{
	if (ContainerType != EContainerType::ECT_MoveFrom || !GameMode)
		return;

	ContainerSize = GameMode->GetNumMoveOptions();

	if (PieceContatinerClass)
	{
		if (!GameMode->GetStartingPieces().IsEmpty())
		{
			for (int32 i = 0; i < ContainerSize; i++)
			{
				USinglePieceContainer* CurrContainer = CreateWidget<USinglePieceContainer>(this, PieceContatinerClass);

				if (!CurrContainer || !MovesPanelBox)
					return;

				MovesPanelBox->AddChild(CurrContainer);
				CurrContainer->HoldPiece(GameMode->GetStartingPieces()[i]);
			}
		}
		else
		{
			GameMode->CreateStartingPieces();
			ConstructMoveFromContainer(GameMode);
		}
	}
}

void UMovesContainer::ConstructMoveToContainer(class ALevelGamemode* GameMode)
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

