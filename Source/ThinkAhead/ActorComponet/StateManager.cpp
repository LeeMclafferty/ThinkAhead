// Copyright © 2023 Lee Mclafferty. All rights reserved. This code is the property of Lee Mclafferty and may not be used for resale, redistribution, or for the purpose of making a profit without written consent from the owner.

#include "ThinkAhead/ActorComponet/StateManager.h"

UStateManager::UStateManager()
	:State(ECubeState::ECS_None)
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UStateManager::BeginPlay()
{
	Super::BeginPlay();
	
}

void UStateManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

