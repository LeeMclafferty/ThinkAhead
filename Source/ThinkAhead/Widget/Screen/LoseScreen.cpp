// Copyright © 2023 Lee Mclafferty. All rights reserved. This code is the property of Lee Mclafferty and may not be used for resale, redistribution, or for the purpose of making a profit without written consent from the owner.


#include "ThinkAhead/Widget/Screen/LoseScreen.h"
#include "Kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"

void ULoseScreen::NativeConstruct()
{

}

void ULoseScreen::PlayLoseSound()
{
	if (!LoseSound)
		return;

	LoseAudioComp = UGameplayStatics::SpawnSound2D(GetWorld(), (USoundBase*)LoseSound);
}

void ULoseScreen::StopLoseSound()
{
	if (LoseAudioComp->IsPlaying())
		LoseAudioComp->Stop();
}
