// Fill out your copyright notice in the Description page of Project Settings.


#include "ThinkAhead/Widget/Menu/MainMenu.h"
#include "Kismet/GameplayStatics.h"

#include "ThinkAhead/Controller/MenuController.h"

void UMainMenu::NativeConstruct()
{

}

void UMainMenu::OnPressPlay()
{
	auto Controller = CheckMenuController();

	if (!Controller)
		return;

	Controller->CreateLevelSelect();
}

void UMainMenu::OnPressOptions()
{
	auto Controller = CheckMenuController();

	if (!Controller)
		return;

	Controller->CreateSettingsMenu();
}

void UMainMenu::OnPressExit()
{
	auto Controller = CheckMenuController();

	if (!Controller)
		return;

	Controller->CreateExitPopup();
} 

class AMenuController* UMainMenu::CheckMenuController()
{
	AMenuController* Controller = Cast<AMenuController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	return Controller;
}
