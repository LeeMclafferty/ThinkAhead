// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ControlledCube.generated.h"

UENUM()
enum class ECubeState : uint8
{
	ECS_None UMETA(DisplayName = "None"),
	ECS_Idle UMETA(DisplayName = "Idle"),
	ECS_MovingNorthSouth UMETA(DisplayName = "MovingNorthSouth"),
	ECS_MoveingEastWest UMETA(DisplayName = "MovingEastWest")
};

UCLASS()
class THINKAHEAD_API AControlledCube : public AActor
{
	GENERATED_BODY()
	
public:	
	AControlledCube();
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintPure)
	ECubeState GetCubeState() { return CubeState; }
	UFUNCTION(BlueprintCallable)
	void SetCubeState(ECubeState NewState) { CubeState = NewState; }

	UPROPERTY(BlueprintReadWrite)
	float CubeSpeed;

	TArray<class UMovePiece*> GetMovesToMake() { return MovesToMake; }
	void AddMoveToMake(class UMovePiece* AddMove);
	void SetCurrentMove(class UMovePiece* NewCurrent);

	UFUNCTION()
	void CheckState();
	UFUNCTION()
	void StartGame() { bIsGameStarted = true; }

	void LookNorth();
	void LookWest();
	void LookSouth();
	void LookEast();

	FVector TraceCheckDir;

protected:
	virtual void BeginPlay() override;

private:

	class ACubeController* CubeController;
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* CubeMesh;
	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* MovementBox;
	UPROPERTY(VisibleAnywhere, Category="Cube|Movement")
	ECubeState CubeState;

	void MoveNorth();
	void MoveWest();
	
	UPROPERTY(VisibleAnywhere, Category="CubeMovement")
	class AGridTile* CurrentTile;
	void SetCurrentTile();

	int32 CheckReach;
	void CheckNextTile();
	FVector SetTraceEndLocation();

	TArray<class UMovePiece*> MovesToMake;
	class UMovePiece* CurrentMove;

	bool bIsGameStarted;

};
