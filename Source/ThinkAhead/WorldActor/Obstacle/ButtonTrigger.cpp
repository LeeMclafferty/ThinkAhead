// Fill out your copyright notice in the Description page of Project Settings.


#include "ThinkAhead/WorldActor/Obstacle/ButtonTrigger.h"

AButtonTrigger::AButtonTrigger()
	:bHasTriggered(false)
{

}

void AButtonTrigger::PerformAction()
{
	if (bHasTriggered)
		return;

	Super::PerformAction();
	bHasTriggered = true;

	// TODO: Start Timer, Make Cube invincible, destroy obstacles that you come in contact with for the duration, make flashing material. 
}
