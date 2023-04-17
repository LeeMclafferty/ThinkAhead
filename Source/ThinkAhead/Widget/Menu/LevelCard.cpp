// Copyright © 2023 Lee Mclafferty. All rights reserved. This code is the property of Lee Mclafferty and may not be used for resale, redistribution, or for the purpose of making a profit without written consent from the owner.


#include "ThinkAhead/Widget/Menu/LevelCard.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

#include "ThinkAhead/GameInstance/ThinkAheadGameInstance.h"

void ULevelCard::NativeConstruct()
{
	LevelNumberText->SetText(LevelToOpenText);
}

void ULevelCard::OpenLevel()
{
	auto GameInst = Cast<UThinkAheadGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (!GameInst)
		return;

	if (GameInst->IsLevelUnlocked(LevelToOpen))
	{
		UGameplayStatics::OpenLevel(GetWorld(), LevelToOpen);
	}
}
