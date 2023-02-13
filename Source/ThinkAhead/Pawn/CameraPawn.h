// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CameraPawn.generated.h"

UCLASS()
class THINKAHEAD_API ACameraPawn : public APawn
{
	GENERATED_BODY()

public:
	ACameraPawn();
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintPure)
	class AControlledCube* GetPlayerCube() { return PlayersCube; }
	void SetPlayerCube( AControlledCube* NewCube);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:	

	UPROPERTY(VisibleAnywhere)
	class USceneComponent* RootComp;
	UPROPERTY(VisibleAnywhere)
	class USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* GameCamera;

	class AControlledCube* PlayersCube;
};
