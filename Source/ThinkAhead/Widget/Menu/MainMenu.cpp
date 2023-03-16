// Fill out your copyright notice in the Description page of Project Settings.


#include "ThinkAhead/Widget/Menu/MainMenu.h"
#include "Kismet/GameplayStatics.h"

#include "ThinkAhead/Controller/MenuController.h"

void UMainMenu::NativeConstruct()
{

}

void UMainMenu::OnPressPlay()
{
	auto Controller = Cast<AMenuController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	if (!Controller)
		return;

	Controller->CreateLevelSelect();
}
