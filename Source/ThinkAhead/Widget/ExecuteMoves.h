// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ExecuteMoves.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnExecute);

UCLASS()
class THINKAHEAD_API UExecuteMoves : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
	void Execute();

	UPROPERTY()
	FOnExecute OnExecute;

private:

	class ACameraPawn* PlayerPawn;
	
};
