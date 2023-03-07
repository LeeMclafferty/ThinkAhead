// Fill out your copyright notice in the Description page of Project Settings.

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

