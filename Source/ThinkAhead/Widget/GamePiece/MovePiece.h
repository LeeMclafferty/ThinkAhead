// Copyright © 2023 Lee Mclafferty. All rights reserved. This code is the property of Lee Mclafferty and may not be used for resale, redistribution, or for the purpose of making a profit without written consent from the owner.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MovePiece.generated.h"

/**
 * 
 */
UCLASS()
class THINKAHEAD_API UMovePiece : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation);
	virtual void NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation);
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent);

	UFUNCTION(BlueprintCallable, Category="CubeControl")
	virtual void Move();

	bool HasActivated();

protected:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UImage* ActionImg;

	class ACubeController* PlayerController;
	class AControlledCube* PlayerCube;

	bool bHasActivated;

	UPROPERTY(EditDefaultsOnly)
	float Speed;

};
