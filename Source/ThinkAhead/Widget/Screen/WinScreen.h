// Copyright © 2023 Lee Mclafferty. All rights reserved. This code is the property of Lee Mclafferty and may not be used for resale, redistribution, or for the purpose of making a profit without written consent from the owner.

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

	UFUNCTION(BlueprintCallable, Category = "Sound")
	void PlayWinSound();
	UFUNCTION(BlueprintCallable, Category = "Sound")
	void StopWinSound();

private:

	UPROPERTY(meta = (BindWidget))
	class UButton* NextLevel;

	UPROPERTY(EditDefaultsOnly, Category="Sound")
	class USoundCue* WinSound;
	class UAudioComponent* WinAudioComp;

	void UnlockNextLevel();
};
