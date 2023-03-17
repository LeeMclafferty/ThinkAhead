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
	UPROPERTY(EditAnywhere, Category="Level")
	FName LevelToOpen;

	UPROPERTY(meta=(BindWidget))
	class UButton* LevelNumButton;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* LevelNumberText;
	UPROPERTY(EditAnywhere, Category="Level")
	FText LevelIndex;
};
