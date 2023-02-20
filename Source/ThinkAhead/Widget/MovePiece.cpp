// Fill out your copyright notice in the Description page of Project Settings.


#include "ThinkAhead/Widget/MovePiece.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/DragDropOperation.h"
#include "Input/Reply.h"

#include "ThinkAhead/Pawn/CameraPawn.h"

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
	if (!PieceClass)
		return;

	SetVisibility(ESlateVisibility::Hidden);

	// Can be passed as payload and used for visual. 
	UMovePiece* DragPiece = CreateWidget<UMovePiece>(this, PieceClass);

	UDragDropOperation* DragDropOp = NewObject<UDragDropOperation>();

	DragDropOp->Payload = DragPiece;
	DragDropOp->DefaultDragVisual = DragPiece;
	DragDropOp->Pivot = EDragPivot::MouseDown;

	OutOperation = DragDropOp;
}

void UMovePiece::NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	SetVisibility(ESlateVisibility::Visible);
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
