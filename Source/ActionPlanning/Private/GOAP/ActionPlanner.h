// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Action.h"
#include "Components/ActorComponent.h"
#include "ActionPlanner.generated.h"


class FParameter;
class AAgentGOAP;
class UAction;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ACTIONPLANNING_API UActionPlanner : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UActionPlanner();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	/**
	 * Used for building up the graph and holding the running costs of actions.
	 */
	class FNode
	{
	public:
		FNode* Parent;
		float RunningCost;
		// State at the end of calculating this Node in BuildGraph
		TMap<FName, FParameter> State;
		UAction* Action;

		FNode(FNode* parent,
			  float runningCost,
			  const TMap<FName, FParameter>& state,
			  UAction* action)
		{
			Parent = parent;
			RunningCost = runningCost;
			State = state;
			Action = action;
		}
	};

	// Return an empty Queue if no plan could be generated or a Queue of plans if successful
	static bool CreateActionPlan(AAgentGOAP* Agent,
											  TArray<UAction*> AvailableActions,
											  TMap<FName, FParameter> WorldState,
											  TMap<FName, FParameter> GoalState,
											  TQueue<UAction*>& OutPlan);

	static bool BuildGraph(FNode* ParentNode, TArray<FNode*>& LeafNodes, TSet<UAction*>& UsableActions, TMap<FName, FParameter>& GoalState);

	/**
		 * Check that all items in 'Test' are in 'Target'. If just one does not match or is not there
		 * then this returns false.
	*/
	static bool InState(const TMap<FName, FParameter>& Test, const TMap<FName, FParameter>& Target);

	/**
	 * @brief Applies the changes from Source state to a copy of Destination state and returns the modified copy 
	 * @return 
	 */
	static TMap<FName, FParameter> ApplyState(const TMap<FName, FParameter>& Source, TMap<FName, FParameter> Destination);

	// Remove an action from a set of actions, and return a copy of the modified action set
	static TSet<UAction*> SubsetActions(TSet<UAction*>& ActionSet, const UAction* RemoveAction);
};
