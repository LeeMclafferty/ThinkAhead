// Fill out your copyright notice in the Description page of Project Settings.


#include "ThinkAhead/Widget/Menu/ConfirmationPopup.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

#include "ThinkAhead/Controller/MenuController.h"

void UConfirmationPopup::NativeConstruct()
{

}

void UConfirmationPopup::GoBack()
{
	auto Controller = Cast<AMenuController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	if (!Controller)
		return;

	Controller->CreateMainMenu();
	
}
