
#include "MoveToState.h"
#include "AIController.h"
#include "GameFramework/Character.h"

void UMoveToState::Initialise(ACharacter* Character, const FVector NewDestination)
{
	Agent = Character;
	Destination = NewDestination;
	if(Agent)
	{
		//Set parthfinding destination to Destination
	}
}

float UMoveToState::GetDistanceToDestination() const
{
	// See if you can get a cost/ path length to return here
	if(const auto Controller = Cast<AAIController>(Agent->GetController()))
	{
		if(const UPathFollowingComponent* PathFollowingComponent = Controller->GetPathFollowingComponent())
		{
			return PathFollowingComponent->GetRemainingPathCost();
		}
	}
	return -1.f;
}

bool UMoveToState::Execute()
{
	/*
	if (_waitForMakingNavMeshPath)
	{
		_waitForMakingNavMeshPath = false;
		return true;
	}

	// This should now be done inside the Action itself
	if (_agent.Movement.HasReachedDestination())
	{
		Debug.DrawLine(_agent.transform.position, _dest, Color.red, 2f, false);
		if ((_agent.transform.position - _dest).magnitude < 0.1f)
		{
			_agent.PerformAction();
			_agent.SetCanvasStatus(true);
		}
		else
		{
			print("Didn't Reach Pos");
			_agent.SetCanvasStatus(true);
		}
		return false;
	}
	*/
	return true;
}