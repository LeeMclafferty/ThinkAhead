// Copyright © 2023 Lee Mclafferty. All rights reserved. This code is the property of Lee Mclafferty and may not be used for resale, redistribution, or for the purpose of making a profit without written consent from the owner.


#include "ThinkAhead/WorldActor/GameBoard/GameBoard.h"
#include "Components/StaticMeshComponent.h"


// Sets default values
AGameBoard::AGameBoard()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoardMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BoardMesh"));
	BoardMesh->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AGameBoard::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGameBoard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

