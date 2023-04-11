// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "OptionsMenu.generated.h"

/**
 * 
 */
UCLASS()
class THINKAHEAD_API UOptionsMenu : public UUserWidget
{
	GENERATED_BODY()


public:
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
	void GoBack();

	UPROPERTY(meta = (BindWidget), SaveGame, BlueprintReadWrite)
	class UCheckBox* OrthoCheckBox;
	UPROPERTY(meta = (BindWidget), SaveGame, BlueprintReadWrite)
	class UCheckBox* SoundCheckBox;
	UPROPERTY(meta = (BindWidget), SaveGame, BlueprintReadWrite)
	class UCheckBox* MusicCheckBox;

protected:


	UFUNCTION(BlueprintCallable)
	void ToggleOrthoCamera();

	void SaveChanges();
	
	void SetCheckBoxes();
};
