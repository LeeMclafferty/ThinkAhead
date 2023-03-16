// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenu.generated.h"

/**
 * 
 */
UCLASS()
class THINKAHEAD_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()
	
public:

	virtual void NativeConstruct() override;

protected:

	UPROPERTY(meta=(BindWidget))
	class UButton* PlayButton;
	UPROPERTY(meta = (BindWidget))
	class UButton* OptionsButton;
	UPROPERTY(meta = (BindWidget))
	class UButton* ExitButton;

	UFUNCTION(BlueprintCallable)
	void OnPressPlay();
};
