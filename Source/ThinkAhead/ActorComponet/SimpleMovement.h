// Copyright © 2023 Lee Mclafferty. All rights reserved. This code is the property of Lee Mclafferty and may not be used for resale, redistribution, or for the purpose of making a profit without written consent from the owner.

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
