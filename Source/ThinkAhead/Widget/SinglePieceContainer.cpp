// Fill out your copyright notice in the Description page of Project Settings.


#include "ThinkAhead/Widget/SinglePieceContainer.h"
#include "Components/Border.h"

#include "ThinkAhead/Widget/MovePiece.h"

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

	if (!HeldPiece)
	{
		UE_LOG(LogTemp, Warning, TEXT("GetHeldPiece() returned null"));
	}
	return HeldPiece;
}
