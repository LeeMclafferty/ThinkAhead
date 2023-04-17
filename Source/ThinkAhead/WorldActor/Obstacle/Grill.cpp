// Copyright © 2023 Lee Mclafferty. All rights reserved. This code is the property of Lee Mclafferty and may not be used for resale, redistribution, or for the purpose of making a profit without written consent from the owner.


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
