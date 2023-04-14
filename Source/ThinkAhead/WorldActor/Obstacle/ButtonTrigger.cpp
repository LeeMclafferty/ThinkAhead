// Fill out your copyright notice in the Description page of Project Settings.


#include "ThinkAhead/WorldActor/Obstacle/ButtonTrigger.h"

AButtonTrigger::AButtonTrigger()
	:bHasTriggered(false)
{

}

void AButtonTrigger::PerformAction()
{
	if (bHasTriggered || !ToInteractWith)
		return;

	Super::PerformAction();
	bHasTriggered = true;

	ToInteractWith->Destroy();
}
