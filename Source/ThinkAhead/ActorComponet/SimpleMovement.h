// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SimpleMovement.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THINKAHEAD_API USimpleMovement : public UActorComponent
{
	GENERATED_BODY()

public:	
	USimpleMovement();

	void LookNorth();
	void LookWest();
	void LookSouth();
	void LookEast();

	void MoveNorth();
	void MoveWest();

	float GetCubeSpeed() { return CubeSpeed; }
	void SetMoveSpeed(float Speed);
		 
	TArray<class UMovePiece*> GetMovesToMake() { return MovesToMake; }
	void AddMoveToMake(class UMovePiece* AddMove);
	void SetCurrentMove(class UMovePiece* NewCurrent);
	void ClearMovesToMake();

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float CubeSpeed;


private:

	TArray<class UMovePiece*> MovesToMake;
	class UMovePiece* CurrentMove;
};
