// Copyright © 2023 Lee Mclafferty. All rights reserved. This code is the property of Lee Mclafferty and may not be used for resale, redistribution, or for the purpose of making a profit without written consent from the owner.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LoseScreen.generated.h"

/**
 * 
 */
UCLASS()
class THINKAHEAD_API ULoseScreen : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable, Category = "Sound")
	void PlayLoseSound();
	UFUNCTION(BlueprintCallable, Category = "Sound")
	void StopLoseSound();

private:

	UPROPERTY(meta = (BindWidget))
	class UButton* RestartButton;

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	class USoundCue* LoseSound;
	class UAudioComponent* LoseAudioComp;
};
