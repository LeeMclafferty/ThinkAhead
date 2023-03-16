// Fill out your copyright notice in the Description page of Project Settings.


#include "ThinkAhead/Controller/MyPlayerController.h"
#include "Blueprint/UserWidget.h"

AMyPlayerController::AMyPlayerController()
{

}

void AMyPlayerController::SetupWidget(TSubclassOf<UUserWidget> WidgetClass)
{
	if (!WidgetClass)
		return;

	ClearViewPort();

	auto Menu = CreateWidget<UUserWidget>(this, WidgetClass);

	CurrentWidget = Menu;
	CurrentWidget->AddToViewport();

}

void AMyPlayerController::ClearViewPort()
{
	if (CurrentWidget)
		CurrentWidget->RemoveFromParent();
}
