// Copyright © 2023 Lee Mclafferty. All rights reserved. This code is the property of Lee Mclafferty and may not be used for resale, redistribution, or for the purpose of making a profit without written consent from the owner.


#include "ThinkAhead/Widget/GamePiece/MovePiece.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/DragDropOperation.h"
#include "Input/Reply.h"
#include "Components/PanelWidget.h"
#include "Components/Image.h"
#include "Components/SizeBox.h"

#include "ThinkAhead/Controller/CubeController.h"
#include "ThinkAhead/Widget/Move/SinglePieceContainer.h"
#include "ThinkAhead/WorldActor/Controlled/ControlledCube.h"
#include "ThinkAhead/Controller/MyPlayerController.h"
#include "ThinkAhead/Widget/Screen/PlayerHud.h"

void UMovePiece::NativeConstruct()
{
	Super::NativeConstruct();

	bHasActivated = false;
}

void UMovePiece::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	auto Owner = GetOwningContainer();

	UDragDropOperation* DragDropOp = NewObject<UDragDropOperation>();
	DragDropOp->Payload = this;
	DragDropOp->Pivot = EDragPivot::MouseDown;
	
	auto DropVisual = CreateWidget<UMovePiece>(this, this->GetClass());
	DragDropOp->DefaultDragVisual = DropVisual;

	Owner->bHasPiece = false;
	OutOperation = DragDropOp;
	ActionImg->SetVisibility(ESlateVisibility::Hidden);
}

void UMovePiece::NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	auto Owner = GetOwningContainer();
	Owner->bHasPiece = true;
	ActionImg->SetVisibility(ESlateVisibility::Visible);
}

FReply UMovePiece::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply Reply =  Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	// will call NativeOnDragDetected when LeftMouseButton is down.
	if (InMouseEvent.GetEffectingButton() != EKeys::LeftMouseButton)
		return Reply;

	Reply.DetectDrag(TakeWidget(), EKeys::LeftMouseButton);
	return Reply;
	
}

void UMovePiece::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	SetHoveredImage();
}

void UMovePiece::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	SetUnHoveredImage();
}

FReply UMovePiece::NativeOnMouseButtonDoubleClick(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply Reply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
	PlayDragtip();

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

class USinglePieceContainer* UMovePiece::GetOwningContainer()
{
	return Cast<USinglePieceContainer>(GetParent()->GetOuter()->GetOuter());
}

void UMovePiece::PlayDragtip()
{
	auto Controller = Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	if (!Controller)
		return;

	Controller->GetPlayerHud()->PlayDragUITip();
}

void UMovePiece::SetHoveredImage()
{
	if (GrabbedImage)
		ActionImg->SetBrushFromTexture(GrabbedImage);
}

void UMovePiece::SetUnHoveredImage()
{
	if (UngrabbedImage)
		ActionImg->SetBrushFromTexture(UngrabbedImage);
}

