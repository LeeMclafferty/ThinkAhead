// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WinScreen.generated.h"

/**
 * 
 */
UCLASS()
class THINKAHEAD_API UWinScreen : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

private:

	UPROPERTY(meta = (BindWidget))
	class UButton* NextLevel;
	
};
