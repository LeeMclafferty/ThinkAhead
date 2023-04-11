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

	void ChangePerspctive();
	void SwapZoomOutLimit();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class USceneComponent* RootComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UCameraComponent* GameCamera;
	
	UFUNCTION(BlueprintCallable)
	void ZoomIn();
	UFUNCTION(BlueprintCallable)
	void ZoomOut();

	UPROPERTY(EditDefaultsOnly, Category="Zoom")
	float ZoomInLimit;
	UPROPERTY(VisibleAnywhere, Category = "Zoom")
	float ZoomOutLimit;

	UPROPERTY(EditDefaultsOnly, Category = "Zoom")
	float OrthoFOV;
	UPROPERTY(EditDefaultsOnly, Category = "Zoom")
	float PerspectiveFOV;

	UPROPERTY(EditDefaultsOnly, Category = "Zoom")
	float OrthZoomLimit;
	UPROPERTY(EditDefaultsOnly, Category = "Zoom")
	float PerspectiveZoomLimit;

private:	

	class AControlledCube* PlayersCube;
	void CheckOrtho();

	class UThinkAheadGameInstance* GameInstance;
};
