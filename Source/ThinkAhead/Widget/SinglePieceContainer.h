// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SinglePieceContainer.generated.h"

/**
 * 
 */
UCLASS()
class THINKAHEAD_API USinglePieceContainer : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	void HoldPiece(class UMovePiece* Held);

	class UMovePiece* GetHeldPiece();

	bool bHasPiece();

protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UBorder* ContainingBorder;

	class UMovePiece* HeldChild;
};
