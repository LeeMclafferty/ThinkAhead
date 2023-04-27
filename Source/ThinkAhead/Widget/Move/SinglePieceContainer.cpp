// Copyright © 2023 Lee Mclafferty. All rights reserved. This code is the property of Lee Mclafferty and may not be used for resale, redistribution, or for the purpose of making a profit without written consent from the owner.


#include "ThinkAhead/Widget/Move/SinglePieceContainer.h"
#include "Components/Border.h"
#include "Components/CanvasPanelSlot.h"

#include "ThinkAhead/Widget/GamePiece/MovePiece.h"

void USinglePieceContainer::NativeConstruct()
{

}

void USinglePieceContainer::HoldPiece(class UMovePiece* Held)
{
	if (!ContainingBorder)
		return;

	ContainingBorder->AddChild(Held);
	bHasPiece = true;
}

bool USinglePieceContainer::HasPiece()
{
	return false;
}

UMovePiece* USinglePieceContainer::GetHeldPiece()
{
	UMovePiece* HeldPiece = Cast<UMovePiece>(ContainingBorder->GetChildAt(0));

	return HeldPiece;
}
