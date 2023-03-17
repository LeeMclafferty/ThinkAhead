// Fill out your copyright notice in the Description page of Project Settings.


#include "ThinkAhead/Widget/Menu/OptionsMenu.h"
#include "Kismet/GameplayStatics.h"

#include "ThinkAhead/Controller/MenuController.h"

void UOptionsMenu::NativeConstruct()
{

}

void UOptionsMenu::GoBack()
{
	auto Controller = Cast<AMenuController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	if (!Controller)
		return;

	Controller->CreateMainMenu();
}
