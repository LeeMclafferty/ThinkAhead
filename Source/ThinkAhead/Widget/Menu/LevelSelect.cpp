// Copyright © 2023 Lee Mclafferty. All rights reserved. This code is the property of Lee Mclafferty and may not be used for resale, redistribution, or for the purpose of making a profit without written consent from the owner.


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
