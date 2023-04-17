// Copyright © 2023 Lee Mclafferty. All rights reserved. This code is the property of Lee Mclafferty and may not be used for resale, redistribution, or for the purpose of making a profit without written consent from the owner.


#include "ThinkAhead/Widget/GamePiece/MovePiece.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/DragDropOperation.h"
#include "Input/Reply.h"
#include "Components/PanelWidget.h"

#include "ThinkAhead/Controller/CubeController.h"
#include "ThinkAhead/Widget/Move/SinglePieceContainer.h"
#include "ThinkAhead/WorldActor/Controlled/ControlledCube.h"

void UMovePiece::NativeConstruct()
{
	Super::NativeConstruct();

	bHasActivated = false;
}

void UMovePiece::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	USinglePieceContainer* Owner = Cast<USinglePieceContainer>(GetParent()->GetOuter()->GetOuter());

	UDragDropOperation* DragDropOp = NewObject<UDragDropOperation>();
	DragDropOp->Payload = this;
	DragDropOp->Pivot = EDragPivot::MouseDown;
	DragDropOp->DefaultDragVisual = this;
	Owner->bHasPiece = false;
	OutOperation = DragDropOp;
}

void UMovePiece::NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	USinglePieceContainer* Owner = Cast<USinglePieceContainer>(GetParent()->GetOuter()->GetOuter());
	Owner->bHasPiece = true;
}

FReply UMovePiece::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply Reply =  Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	// will call NativeOnDragDetected when LeftMouseButton is down.
	if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
	{
		Reply.DetectDrag(TakeWidget(), EKeys::LeftMouseButton);
		return Reply;
	}

	return Reply;
}

void UMovePiece::Move()
{
	if (ACubeController* Controller = Cast<ACubeController>(UGameplayStatics::GetPlayerController(GetWorld(), 0)))
	{
		if (Controller->GetControlledCube())
		{
			PlayerController = Controller;
			bHasActivated = true;
		}
	}
	if (AControlledCube* CC = Cast<AControlledCube>(PlayerController->GetControlledCube()))
	{
		PlayerCube = CC;
	}
	Speed = 10.f;
}

bool UMovePiece::HasActivated()
{
	return bHasActivated;
}

void UMovePiece::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

}
