// Copyright © 2023 Lee Mclafferty. All rights reserved. This code is the property of Lee Mclafferty and may not be used for resale, redistribution, or for the purpose of making a profit without written consent from the owner.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MovesContainer.generated.h"

/**
 * 
 */
UENUM()
enum class EContainerType : uint8
{
	ECT_None UMETA(DisplayName = "None"),
	ECT_MoveFrom UMETA(DisplayName = "Move From"),
	ECT_MoveTo UMETA(DisplayName = "Move To")
};

UCLASS()
class THINKAHEAD_API UMovesContainer : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	virtual bool NativeOnDrop(const FGeometry& InGeomtry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

	UPanelWidget* GetMovesPanelBox() { return MovesPanelBox; }
protected:

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UImage* ContainerImage;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UPanelWidget* MovesPanelBox;
	
	int32 ContainerSize;

	UPROPERTY(EditDefaultsOnly, Category="Initialize|TSubclassOf")
	TSubclassOf<class USinglePieceContainer> PieceContatinerClass;

	UPROPERTY(EditDefaultsOnly, Category="Initialize")
	EContainerType ContainerType;

	bool AddMovePiece(class UMovePiece* ToAdd);

	UFUNCTION(BlueprintCallable)
	void ConstructMoveFromContainer(class ALevelGamemode* GameMode);
	UFUNCTION(BlueprintCallable)
	void ConstructMoveToContainer(class ALevelGamemode* GameMode);
private:

	UPROPERTY(EditDefaultsOnly, Category = "Sounds")
	class USoundCue* DropSound;
};
