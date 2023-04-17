// Copyright © 2023 Lee Mclafferty. All rights reserved. This code is the property of Lee Mclafferty and may not be used for resale, redistribution, or for the purpose of making a profit without written consent from the owner.

#pragma once

#include "CoreMinimal.h"
#include "ThinkAhead/Controller/MyPlayerController.h"
#include "CubeController.generated.h"

/**
 * 
 */
UCLASS()
class THINKAHEAD_API ACubeController : public AMyPlayerController
{
	GENERATED_BODY()

public: 
	ACubeController();

	virtual void BeginPlay() override;
	class UExecuteMoves* GetExecuteButton() { return ExecuteButton; }
	class AControlledCube* GetControlledCube() { return ControlledCube; }

	void SetControlledCube(class AControlledCube* NewCube);

protected:


private:
	class UExecuteMoves* ExecuteButton;
	UPROPERTY(VisibleAnywhere)
	class AControlledCube* ControlledCube;
	
};
