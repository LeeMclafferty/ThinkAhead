// Fill out your copyright notice in the Description page of Project Settings.


#include "ThinkAhead/WorldActor/Obstacle/Grill.h"

#include "ThinkAhead/WorldActor/Controlled/ControlledCube.h"

AGrill::AGrill()
{

}

void AGrill::PerformAction()
{
	Super::PerformAction();

	
	Destroy();
}
