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

private:

	UPROPERTY(meta = (BindWidget))
	class UButton* RestartButton;
};
