// Fill out your copyright notice in the Description page of Project Settings.


#include "ThinkAhead/Widget/Menu/LevelSelect.h"
#include "Kismet/GameplayStatics.h"

#include "ThinkAhead/Widget/Menu/MainMenu.h"
#include "ThinkAhead/Controller/MenuController.h"

void ULevelSelect::NativeConstruct()
{

}

void ULevelSelect::OnPressBack()
{
	auto Controller = Cast<AMenuController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	if (!Controller)
		return;

	Controller->CreateMainMenu();
}
