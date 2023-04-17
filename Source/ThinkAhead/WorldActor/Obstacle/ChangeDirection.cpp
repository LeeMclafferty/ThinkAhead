// Copyright © 2023 Lee Mclafferty. All rights reserved. This code is the property of Lee Mclafferty and may not be used for resale, redistribution, or for the purpose of making a profit without written consent from the owner.


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
