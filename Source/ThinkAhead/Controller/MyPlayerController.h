// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class THINKAHEAD_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	AMyPlayerController();

	void SetupWidget(TSubclassOf<UUserWidget> WidgetClass);

protected:
	virtual void Tick(float DeltaTime) override;

	void ClearViewPort();

	UUserWidget* GetCurrentWidget() { return CurrentWidget; }

private:
	UUserWidget* CurrentWidget;
	
};