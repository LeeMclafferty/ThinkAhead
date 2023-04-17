// Copyright © 2023 Lee Mclafferty. All rights reserved. This code is the property of Lee Mclafferty and may not be used for resale, redistribution, or for the purpose of making a profit without written consent from the owner.
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StateManager.generated.h"

UENUM()
enum class ECubeState : uint8
{
	ECS_None UMETA(DisplayName = "None"),
	ECS_Idle UMETA(DisplayName = "Idle"),
	ECS_MovingNorthSouth UMETA(DisplayName = "MovingNorthSouth"),
	ECS_MoveingEastWest UMETA(DisplayName = "MovingEastWest")
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THINKAHEAD_API UStateManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	UStateManager();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintPure)
	ECubeState GetState() { return State; }
	UFUNCTION(BlueprintCallable)
	void SetState(ECubeState NewState) { State = NewState; }

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Cube|Movement")
	ECubeState State;
	

		
};
