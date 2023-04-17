// Copyright Epic Games, Inc. All Rights Reserved.


#include "ThinkAheadGameModeBase.h"
#include "Kismet/GameplayStatics.h"

#include "ThinkAhead/GameInstance/ThinkAheadGameInstance.h"
#include "ThinkAhead/Controller/CubeController.h"
#include "ThinkAhead/ActorComponet/SoundManager.h"


AThinkAheadGameModeBase::AThinkAheadGameModeBase()
	:bShouldPlayTransition(true)
{
	SoundManager = CreateDefaultSubobject<USoundManager>(TEXT("Sound Manager"));
}

void AThinkAheadGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	
	LoadGame();

	if (SoundManager)
	{
		SoundManager->PlayMusic();
		SoundManager->PlayAmbientSounds();
	}
}

void AThinkAheadGameModeBase::ToggleOrtho()
{

	UThinkAheadGameInstance* GameInst = Cast<UThinkAheadGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (!GameInst)
		return;

	bool bIsOrtho = (GameInst->IsOrtho()) ? false : true;
	GameInst->SetIsOrtho(bIsOrtho);
}

void AThinkAheadGameModeBase::ToggleMusic()
{
	UThinkAheadGameInstance* GameInst = Cast<UThinkAheadGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (!GameInst)
		return;

	bool bIsMusic = (GameInst->IsMusicOn()) ? false : true;
	GameInst->SetIsMusicOn(bIsMusic);
}

void AThinkAheadGameModeBase::ToggleSounds()
{
	UThinkAheadGameInstance* GameInst = Cast<UThinkAheadGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (!GameInst)
		return;
	
	bool bIsSound = (GameInst->IsSoundOn()) ? false : true;
	GameInst->SetIsSoundOn(bIsSound);
}

void AThinkAheadGameModeBase::LoadGame()
{
	UThinkAheadGameInstance* GameInst = Cast<UThinkAheadGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (!GameInst)
		return;

	GameInst->LoadGame();
}

