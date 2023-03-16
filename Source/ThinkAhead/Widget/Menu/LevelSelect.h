// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LevelSelect.generated.h"

/**
 * 
 */
UCLASS()
class THINKAHEAD_API ULevelSelect : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

protected:

	UPROPERTY(meta=(BindWidget))
	class UButton* BackButton;

	UFUNCTION(BlueprintCallable)
	void OnPressBack();
};
