// Fill out your copyright notice in the Description page of Project Settings.


#include "ThinkAhead/WorldActor/Obstacle/ChangeDirection.h"

#include "ThinkAhead/Widget/GamePiece/MovePiece.h"

AChangeDirection::AChangeDirection()
{

}

void AChangeDirection::PerformAction()
{
	Super::PerformAction();

	if (!MoveClass)
		return;

	MoveDirection = CreateWidget<UMovePiece>(GetWorld(), MoveClass);

	if (MoveDirection)
		MoveDirection->Move();

	// Add Material Change here to signified that it is now inactive.

	ObstacleMesh->SetCollisionProfileName("NoCollision");
}
