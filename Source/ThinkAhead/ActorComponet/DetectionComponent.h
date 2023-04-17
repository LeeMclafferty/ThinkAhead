// Copyright © 2023 Lee Mclafferty. All rights reserved. This code is the property of Lee Mclafferty and may not be used for resale, redistribution, or for the purpose of making a profit without written consent from the owner.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DetectionComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THINKAHEAD_API UDetectionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UDetectionComponent();

	void SetCurrentTile();
	class AGridTile* GetCurrentTile() { return CurrentTile; }
	FHitResult TraceUnderActor(ECollisionChannel TraceChannel);

	FHitResult TraceInFrontActor(ECollisionChannel TraceChannel);
	FHitResult TraceInFrontActor(ECollisionChannel TraceChannel, FVector TraceDirection);

protected:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void BeginPlay() override;

private:	
	class AGridTile* CurrentTile;
		
};
