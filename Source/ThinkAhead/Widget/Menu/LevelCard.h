// Fill out your copyright notice in the Description page of Project Settings.

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

	UPROPERTY(EditAnywhere, Category="Level")
	ULevel* Level;
};
