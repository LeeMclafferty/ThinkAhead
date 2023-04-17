// Copyright © 2023 Lee Mclafferty. All rights reserved. This code is the property of Lee Mclafferty and may not be used for resale, redistribution, or for the purpose of making a profit without written consent from the owner.

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
	UFUNCTION(BlueprintCallable)
	void ToggleMusic();
	UFUNCTION(BlueprintCallable)
	void ToggleSounds();

	void SaveChanges();
	
	void SetCheckBoxes();
};
