// Fill out your copyright notice in the Description page of Project Settings.

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
