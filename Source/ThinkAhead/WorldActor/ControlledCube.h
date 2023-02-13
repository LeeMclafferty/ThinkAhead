// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ControlledCube.generated.h"

UENUM()
enum class ECubeState : uint8
{
	ECS_Idle UMETA(DisplayName = "Idle"),
	ECS_Moving UMETA(DisplayName = "Moving")
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
protected:
	virtual void BeginPlay() override;


private:
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* CubeMesh;
	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* MovementBox;
	UPROPERTY(VisibleAnywhere, Category="Cube|Movement")
	ECubeState CubeState;

	void MoveForward();
	void MoveRight();
	
	UPROPERTY(VisibleAnywhere, Category="CubeMovement")
	class AGridTile* CurrentTile;
	void SetCurrentTile();

	void CheckNextTile();

};
