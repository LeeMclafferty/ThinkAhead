
#include "ThinkAhead/ActorComponet/SimpleMovement.h"

USimpleMovement::USimpleMovement()
	:CubeSpeed(10.f)
{
	PrimaryComponentTick.bCanEverTick = true;

}

void USimpleMovement::BeginPlay()
{
	Super::BeginPlay();

}

void USimpleMovement::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void USimpleMovement::LookNorth()
{
	FRotator CurrentRotation = GetOwner()->GetActorRotation();
	CurrentRotation.Yaw = 0.f;
	GetOwner()->SetActorRotation(CurrentRotation);
}

void USimpleMovement::LookWest()
{
	FRotator CurrentRotation = GetOwner()->GetActorRotation();
	CurrentRotation.Yaw = -90.f;
	GetOwner()->SetActorRotation(CurrentRotation);
}

void USimpleMovement::LookSouth()
{
	FRotator CurrentRotation = GetOwner()->GetActorRotation();
	CurrentRotation.Yaw = 180.f;
	GetOwner()->SetActorRotation(CurrentRotation);
}

void USimpleMovement::LookEast()
{
	FRotator CurrentRotation = GetOwner()->GetActorRotation();
	CurrentRotation.Yaw = 90.f;
	GetOwner()->SetActorRotation(CurrentRotation);
}

void USimpleMovement::MoveNorth()
{
	FVector Target = GetOwner()->GetActorLocation() += FVector(0.f, CubeSpeed, 0.f);
	GetOwner()->SetActorLocation(FMath::Lerp(GetOwner()->GetActorLocation(), Target, 1.f));
}

void USimpleMovement::MoveWest()
{
	FVector Target = GetOwner()->GetActorLocation() += FVector(CubeSpeed, 0.f, 0.f);
	GetOwner()->SetActorLocation(FMath::Lerp(GetOwner()->GetActorLocation(), Target, 1.f));
}

void USimpleMovement::SetMoveSpeed(float Speed)
{
	CubeSpeed = Speed;
}

void USimpleMovement::AddMoveToMake(class UMovePiece* AddMove)
{
	if (AddMove)
		MovesToMake.Add(AddMove);
}

void USimpleMovement::SetCurrentMove(class UMovePiece* NewCurrent)
{
	CurrentMove = NewCurrent;
}

void USimpleMovement::ClearMovesToMake()
{
	MovesToMake.Empty();
}
