// Copyright © 2023 Lee Mclafferty. All rights reserved. This code is the property of Lee Mclafferty and may not be used for resale, redistribution, or for the purpose of making a profit without written consent from the owner.

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
	UPROPERTY(VisibleAnywhere)
	class UDetectionComponent* DetectionComponent;

	class ACubeController* PlayerController;
	class AControlledCube* PlayerCube;

	class AGridTile* GetPlayersCurrentTile();
	AGridTile* CurrentTile;

	UPROPERTY(EditDefaultsOnly, Category="Sounds")
	class USoundCue* ContactSound;

private:

	void SetStartingTile();
	void PlayContactSound();


};
