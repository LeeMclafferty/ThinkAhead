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

	bool IsGameStarted() { return bIsGameStarted; }

	void OnDeath();
	class UDetectionComponent* GetDetectionComponent() { return DetectionComponent; }

	void SetDeathMesh(class UStaticMesh* Mesh) { DeathMesh = Mesh; }
	void SetDeathVFX(class UNiagaraSystem* VFX) { DeathVFX = VFX; }
protected:
	virtual void BeginPlay() override;

private:

	class ACubeController* CubeController;
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* CubeMesh;
	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* MovementBox;
	UPROPERTY(VisibleAnywhere)
	class UDetectionComponent* DetectionComponent;

	int32 CheckReach;
	void CheckForObstacle();
	FVector SetTraceEndDirection();
	
	UPROPERTY(VisibleAnywhere)
	class USimpleMovement* SimpleMovementComponent;
	UPROPERTY(VisibleAnywhere)
	class UStateManager* StateManager;

	bool bIsGameStarted;

	void OnIdle();

	UPROPERTY(EditDefaultsOnly, Category = "OnDeath")
	class UStaticMesh* DeathMesh;
	UPROPERTY(EditDefaultsOnly, Category = "OnDeath")
	class UNiagaraSystem* DeathVFX;
};
