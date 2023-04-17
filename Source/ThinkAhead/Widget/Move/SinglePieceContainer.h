// Copyright © 2023 Lee Mclafferty. All rights reserved. This code is the property of Lee Mclafferty and may not be used for resale, redistribution, or for the purpose of making a profit without written consent from the owner.

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
	bool HasPiece();
	class UMovePiece* GetHeldPiece();
	
	bool bHasPiece;
protected:

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UBorder* ContainingBorder;
};
