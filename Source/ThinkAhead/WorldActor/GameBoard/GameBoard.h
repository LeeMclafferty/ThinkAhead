// Copyright © 2023 Lee Mclafferty. All rights reserved. This code is the property of Lee Mclafferty and may not be used for resale, redistribution, or for the purpose of making a profit without written consent from the owner.

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
