// Copyright © 2023 Lee Mclafferty. All rights reserved. This code is the property of Lee Mclafferty and may not be used for resale, redistribution, or for the purpose of making a profit without written consent from the owner.


#include "ThinkAhead/Widget/Move/SinglePieceContainer.h"
#include "Components/Border.h"
#include "Components/CanvasPanelSlot.h"

#include "ThinkAhead/Widget/GamePiece/MovePiece.h"

void USinglePieceContainer::NativeConstruct()
{
	//Super::NativeConstruct();

// 	UPanelSlot* RootSlot = Cast<UPanelSlot>(GetRootWidget()->Slot);
// 	if (RootSlot)
// 	{
// 		// Set the size and alignment properties here.
// 		// For example, if the root widget is inside a Canvas Panel:
// 		UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(RootSlot);
// 		if (CanvasSlot)
// 		{
// 			CanvasSlot->SetAutoSize(true); // Enable or disable auto size
// 			CanvasSlot->SetSize(FVector2D(150.f, 150.f)); // Set explicit size
// 			CanvasSlot->SetAlignment(FVector2D(0.0f, 0.0f)); // Set alignment
// 		}
// 	}
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

	if (!HeldPiece)
	{
		UE_LOG(LogTemp, Warning, TEXT("GetHeldPiece() returned null"));
	}
	return HeldPiece;
}
