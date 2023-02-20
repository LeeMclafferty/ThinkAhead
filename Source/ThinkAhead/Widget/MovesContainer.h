// Fill out your copyright notice in the Description page of Project Settings.

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

protected:

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UImage* ContainerImage;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UPanelWidget* MovesPanelBox;
	
	int32 ContainerSize;

	UPROPERTY(EditDefaultsOnly, Category="Initialize|TSubclassOf")
	TSubclassOf<class USinglePieceContainer> PieceContatinerClass;

private:
	UPROPERTY(EditDefaultsOnly, Category="Initialize")
	EContainerType ContainerType;

	bool AddMovePiece(class UMovePiece* ToAdd);

	void ConstructMoveFromContainer(class AThinkAheadGameModeBase* GameMode);
	void ConstructMoveToContainer(class AThinkAheadGameModeBase* GameMode);
};
