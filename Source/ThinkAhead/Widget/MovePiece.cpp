// Fill out your copyright notice in the Description page of Project Settings.


#include "ThinkAhead/Widget/MovePiece.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/DragDropOperation.h"
#include "Input/Reply.h"
#include "Components/PanelWidget.h"

#include "ThinkAhead/Pawn/CameraPawn.h"
#include "ThinkAhead/Widget/SinglePieceContainer.h"

void UMovePiece::NativeConstruct()
{
	Super::NativeConstruct();

	if (ACameraPawn* PP = Cast<ACameraPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0)))
	{
		PlayerPawn = PP;
	}
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
	if (ACameraPawn* PP = Cast<ACameraPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0)))
	{
		if (PP->GetPlayerCube())
		{
			PlayerPawn = PP;
		}
	}
}

void UMovePiece::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

}
