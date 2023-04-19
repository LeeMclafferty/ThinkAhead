// Copyright © 2023 Lee Mclafferty. All rights reserved. This code is the property of Lee Mclafferty and may not be used for resale, redistribution, or for the purpose of making a profit without written consent from the owner.


#include "ThinkAhead/ActorComponet/SoundManager.h"
#include "Kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"

#include "ThinkAhead/GameInstance/ThinkAheadGameInstance.h"

USoundManager::USoundManager()
:MusicVolume(.1f), SoundsVolume(.05f)
{
	PrimaryComponentTick.bCanEverTick = true;

}

void USoundManager::BeginPlay()
{
	Super::BeginPlay();

}

void USoundManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void USoundManager::StopAmbientSounds()
{
		
	if (NatureAudioComp->IsPlaying() && StreamAudioComp->IsPlaying())
	{
		NatureAudioComp->Stop();
		StreamAudioComp->Stop();
	}
	
	
		
}

void USoundManager::StopMusic()
{
	if (MusicAudioComp->IsPlaying())
	{
		MusicAudioComp->Stop();
	}
}

void USoundManager::PlayAmbientSounds()
{
	UThinkAheadGameInstance* GameInst = Cast<UThinkAheadGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (!NatureSound || !StreamSound || !GameInst)
		return;

	if (!GameInst->IsSoundOn())
		return;

	NatureAudioComp = UGameplayStatics::SpawnSound2D(GetWorld(), (USoundBase*)NatureSound, SoundsVolume);
	StreamAudioComp = UGameplayStatics::SpawnSound2D(GetWorld(), (USoundBase*)StreamSound, SoundsVolume);
}

void USoundManager::PlayMusic()
{
	UThinkAheadGameInstance* GameInst = Cast<UThinkAheadGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (!BackgroundMusic || !GameInst)
		return;

	if (!GameInst->IsMusicOn())
		return;

	MusicAudioComp = UGameplayStatics::SpawnSound2D(GetWorld(), (USoundBase*)BackgroundMusic, MusicVolume);
}


