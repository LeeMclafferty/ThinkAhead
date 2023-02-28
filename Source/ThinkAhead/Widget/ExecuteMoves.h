// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ExecuteMoves.generated.h"

/**
 * 
 */
UCLASS()
class THINKAHEAD_API UExecuteMoves : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
	void Execute();

private:

	class ACameraPawn* PlayerPawn;
	
};
