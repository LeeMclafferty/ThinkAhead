// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameBoard.generated.h"

UCLASS()
class THINKAHEAD_API AGameBoard : public AActor
{
	GENERATED_BODY()
	
public:	
	AGameBoard();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* BoardMesh;


};
