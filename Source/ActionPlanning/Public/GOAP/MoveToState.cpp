#include "GOAP/MoveToState.h"
#include "NavigationPath.h"
#include "NavigationSystem.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

UMoveToState::UMoveToState()
{
	Agent = nullptr;
	DestinationActor = nullptr;
	DestinationLocation = FVector::Zero();
	TetherDistance = 250.f;
	LastPointIndex = 0;
	PathLength = 0;
}

void UMoveToState::InitialiseLocation(ACharacter* Character, const FVector& Destination)
{
	Agent = Character;
	DestinationLocation = Destination;
	if(Character)
	{
		NavPath = UNavigationSystemV1::FindPathToLocationSynchronously(
			Character, Character->GetActorLocation(), DestinationLocation, Character);
	}
	if(!NavPath->IsValid())
	{
		//maybe try async
		// or path to projected location
		return;
	}
	
	PathPoints = NavPath->GetPath()->GetPathPoints();
}

void UMoveToState::InitialiseActor(ACharacter* Character, AActor* Destination)
{
	Agent = Character;
	DestinationActor = Destination;
	if(Character)
	{
		NavPath = UNavigationSystemV1::FindPathToActorSynchronously(
			Character, Character->GetActorLocation(), DestinationActor, TetherDistance, Character);
	}
	if(!NavPath->IsValid())
	{
		//maybe try async
		return;
	}
	
	PathPoints = NavPath->GetPath()->GetPathPoints();
	PathLength = NavPath->GetPathLength();
}

bool UMoveToState::IncreasePathPointIndex()
{
	if(++LastPointIndex >= PathPoints.Num())
	{
		// reached destination
		// maybe perform action
		return false;
	}
	
	NextPointLocation = PathPoints[LastPointIndex].Location;
	CurrentNormal = (NextPointLocation - Agent->GetActorLocation()).GetSafeNormal();
	CurrentNormalRotator = CurrentNormal.ToOrientationRotator();
	return true;
}

bool UMoveToState::Execute(const float DeltaTime)
{
	if(PathPoints.Num() == 0)
	{
		return false;
	}
	
	const FVector CharacterLocation = Agent->GetActorLocation();
	const FVector DesiredLocation = CharacterLocation + CurrentNormal * (DeltaTime * MoveSpeed);
	//Agent->SetActorLocationAndRotation(DesiredLocation, CurrentNormalRotator);

	Agent->GetCharacterMovement()->MoveSmooth(CurrentNormal * MoveSpeed, DeltaTime);	

	if(FVector::Dist(CharacterLocation, NextPointLocation) < 25.f)
	{
		// reached point
		// add snap to pathpoint if last point
		return IncreasePathPointIndex();
	}
	return true;
}
