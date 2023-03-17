// Fill out your copyright notice in the Description page of Project Settings.


#include "ThinkAhead/Widget/Menu/LevelCard.h"
#include "Components/TextBlock.h"

void ULevelCard::NativeConstruct()
{
	LevelNumberText->SetText(LevelIndex);
}
