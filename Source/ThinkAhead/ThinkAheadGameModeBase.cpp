// Copyright Epic Games, Inc. All Rights Reserved.


#include "ThinkAheadGameModeBase.h"
#include "Kismet/GameplayStatics.h"

#include "ThinkAhead/GameInstance/ThinkAheadGameInstance.h"
#include "ThinkAhead/Controller/CubeController.h"


AThinkAheadGameModeBase::AThinkAheadGameModeBase()
{

}

void AThinkAheadGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	LoadGame();
}

void AThinkAheadGameModeBase::ToggleOrtho()
{

	UThinkAheadGameInstance* GameInst = Cast<UThinkAheadGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (!GameInst)
		return;

	bool bIsOrtho = (GameInst->IsOrtho()) ? false : true;
	GameInst->SetIsOrtho(bIsOrtho);
}

void AThinkAheadGameModeBase::LoadGame()
{
	UThinkAheadGameInstance* GameInst = Cast<UThinkAheadGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (!GameInst)
		return;

	GameInst->LoadGame();
}
