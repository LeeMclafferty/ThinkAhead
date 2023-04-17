// Copyright © 2023 Lee Mclafferty. All rights reserved. This code is the property of Lee Mclafferty and may not be used for resale, redistribution, or for the purpose of making a profit without written consent from the owner.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LevelCard.generated.h"

/**
 * 
 */
UCLASS()
class THINKAHEAD_API ULevelCard : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintPure)
	FName GetLevelToOpen() { return LevelToOpen; }

protected:
	//Open level by name
	UPROPERTY(EditAnywhere, Category="Level")
	FName LevelToOpen;

	UPROPERTY(meta=(BindWidget))
	class UButton* LevelNumButton;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* LevelNumberText;

	//Set LevelCard text
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FText LevelToOpenText;

	UFUNCTION(BlueprintCallable)
	void OpenLevel();
	UFUNCTION(BlueprintPure)
	bool CanOpenLevel();

	UPROPERTY(EditAnywhere, Category="Level")
	ULevel* Level;
};
