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
	
};
