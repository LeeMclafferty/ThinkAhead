// Fill out your copyright notice in the Description page of Project Settings.


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
