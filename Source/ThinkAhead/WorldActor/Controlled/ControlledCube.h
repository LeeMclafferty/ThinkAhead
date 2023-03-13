// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ThinkAhead/ActorComponet/StateManager.h"
#include "ControlledCube.generated.h"



UCLASS()
class THINKAHEAD_API AControlledCube : public AActor
{
	GENERATED_BODY()
	
public:	
	AControlledCube();
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void CheckState();
	UFUNCTION()
	void StartGame() { bIsGameStarted = true; }

	FVector TraceCheckDir;

	class USimpleMovement* GetSimpleMovementComp() { return SimpleMovementComponent; }
	class UStateManager* GetStateManger() { return StateManager; }
	ECubeState GetCubeState();
	void SetCubeState(ECubeState NewState);

	class AGridTile* GetCurrentTile() { return CurrentTile; }

	bool IsGameStarted() { return bIsGameStarted; }

protected:
	virtual void BeginPlay() override;

private:

	class ACubeController* CubeController;
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* CubeMesh;
	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* MovementBox;

	UPROPERTY(VisibleAnywhere, Category="CubeMovement")
	class AGridTile* CurrentTile;
	void SetCurrentTile();

	FHitResult TraceUnderCube(ECollisionChannel TraceChannel);

	FHitResult TraceInFrontCube(ECollisionChannel TraceChannel);

	int32 CheckReach;
	void CheckForObstacle();
	FVector SetTraceEndDirection();
	
	UPROPERTY(VisibleAnywhere)
	class USimpleMovement* SimpleMovementComponent;
	UPROPERTY(VisibleAnywhere)
	class UStateManager* StateManager;

	bool bIsGameStarted;

	void OnIdle();
};
