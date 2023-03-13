// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Obstacle.generated.h"

UCLASS()
class THINKAHEAD_API AObstacle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AObstacle();
	virtual void Tick(float DeltaTime) override;

	virtual void PerformAction();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* ObstacleMesh;

	class ACameraPawn* PlayerPawn;
	class AControlledCube* PlayerCube;

	class AGridTile* GetPlayersCurrentTile();

private:


};
