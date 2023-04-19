// Copyright © 2023 Lee Mclafferty. All rights reserved. This code is the property of Lee Mclafferty and may not be used for resale, redistribution, or for the purpose of making a profit without written consent from the owner.


#include "ThinkAhead/Widget/Screen/WinScreen.h"
#include "Kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"

void UWinScreen::NativeConstruct()
{

}

void UWinScreen::PlayWinSound()
{
	if (!WinSound)
		return;

	WinAudioComp = UGameplayStatics::SpawnSound2D(GetWorld(), (USoundBase*)WinSound);
}

void UWinScreen::StopWinSound()
{
	if (WinAudioComp->IsPlaying())
		WinAudioComp->Stop();
}
