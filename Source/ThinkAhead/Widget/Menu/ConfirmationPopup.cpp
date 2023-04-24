// Copyright © 2023 Lee Mclafferty. All rights reserved. This code is the property of Lee Mclafferty and may not be used for resale, redistribution, or for the purpose of making a profit without written consent from the owner.


#include "ThinkAhead/Widget/Menu/ConfirmationPopup.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

#include "ThinkAhead/Controller/MenuController.h"

void UConfirmationPopup::NativeConstruct()
{

}

void UConfirmationPopup::GoBack()
{
	auto Controller = Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	if (!Controller)
		return;

	Controller->CreatePreviousWidget();
	
}
