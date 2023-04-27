// Copyright © 2023 Lee Mclafferty. All rights reserved. This code is the property of Lee Mclafferty and may not be used for resale, redistribution, or for the purpose of making a profit without written consent from the owner.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerHud.generated.h"

/**
 * 
 */
UCLASS()
class THINKAHEAD_API UPlayerHud : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	class UMoveToContainer* GetMoveToPanel() { return MoveToPanel; }
	class UMovesContainer* GetMoveFromPanel() { return MoveFromPanel; }
	class UExecuteMoves* GetExecuteButton() { return ExecuteButton; }

	UFUNCTION(BlueprintImplementableEvent)
	void PlayDragUITip();

protected:
	class ACameraPawn* PlayerPawn;

	UPROPERTY(meta=(BindWidget))
	class UMoveToContainer* MoveToPanel;
	UPROPERTY(meta = (BindWidget))
	class UMovesContainer* MoveFromPanel;
	//No bind since it is part of the MoveToPanel, not the UPlayerHud. 
	class UExecuteMoves* ExecuteButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* RestartButton;

	UFUNCTION(BlueprintCallable)
	void ResartLevel();

	UFUNCTION(BlueprintCallable)
	void SwapPerspective();

private:
	void PopulateGamePieces();
	void SetControllerExecuteButton();
};
