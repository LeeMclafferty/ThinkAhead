// Fill out your copyright notice in the Description page of Project Settings.


#include "ThinkAhead/Widget/SinglePieceContainer.h"
#include "Components/Border.h"

#include "ThinkAhead/Widget/MovePiece.h"

void USinglePieceContainer::NativeConstruct()
{

}

void USinglePieceContainer::HoldPiece(class UMovePiece* Held)
{
	if (!Held || !ContainingBorder)
		return;

	ContainingBorder->AddChild(Held);
	HeldChild = Held;
}

class UMovePiece* USinglePieceContainer::GetHeldPiece()
{
	return HeldChild;
}

bool USinglePieceContainer::bHasPiece()
{
	if (HeldChild)
		return true;

	return false;
}
