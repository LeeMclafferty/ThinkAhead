// Fill out your copyright notice in the Description page of Project Settings.


#include "ThinkAhead/ActorComponet/DetectionComponent.h"

#include "ThinkAhead/WorldActor/Grid/GridTile.h"

UDetectionComponent::UDetectionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UDetectionComponent::BeginPlay()
{
	Super::BeginPlay();

}

FHitResult UDetectionComponent::TraceUnderActor(ECollisionChannel TraceChannel)
{
	FVector StartLocation = GetOwner()->GetActorLocation();
	FVector EndLocation = GetOwner()->GetActorLocation() - FVector(0.f, 0.f, 100.f);
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(GetOwner());
	FHitResult OutHit;

	GetWorld()->LineTraceSingleByChannel(OutHit, StartLocation, EndLocation, TraceChannel, Params);

	return OutHit;
}

FHitResult UDetectionComponent::TraceInFrontActor(ECollisionChannel TraceChannel)
{
	FVector OwnerLocation = GetOwner()->GetActorLocation();

	FVector StartLocation = FVector(OwnerLocation.X, OwnerLocation.Y, OwnerLocation.Z + 50.f);
	FVector EndLocation = GetOwner()->GetActorForwardVector();
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(GetOwner());
	FHitResult OutHit;

	GetWorld()->LineTraceSingleByChannel(OutHit, StartLocation, EndLocation, TraceChannel, Params);
	return OutHit;
}

FHitResult UDetectionComponent::TraceInFrontActor(ECollisionChannel TraceChannel, FVector TraceDirection)
{
	FVector OwnerLocation = GetOwner()->GetActorLocation();

	FVector StartLocation = FVector(OwnerLocation.X, OwnerLocation.Y, OwnerLocation.Z + 50.f);
	FVector EndLocation = TraceDirection;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(GetOwner());
	FHitResult OutHit;

	GetWorld()->LineTraceSingleByChannel(OutHit, StartLocation, EndLocation, TraceChannel, Params);
	return OutHit;
}

void UDetectionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UDetectionComponent::SetCurrentTile()
{
	FHitResult OutHit = TraceUnderActor(ECC_GameTraceChannel2);

	if (!OutHit.GetActor())
		return;

	if (auto TileActor = Cast<AGridTile>(OutHit.GetActor()))
	{
		if (TileActor == CurrentTile)
			return;

		CurrentTile = TileActor;
	}
}

