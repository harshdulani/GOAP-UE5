// Fill out your copyright notice in the Description page of Project Settings.

#include "GOAP/ActionPlanner.h"
#include "GOAP/Action.h"
#include "FParameter.h"

// Sets default values for this component's properties
UActionPlanner::UActionPlanner()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UActionPlanner::BeginPlay()
{
	Super::BeginPlay();

	// ...
}

// Called every frame
void UActionPlanner::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UActionPlanner::CreateActionPlan(AAgentGOAP* Agent,
									   TArray<UAction*> AvailableActions,
									   TMap<FName, FParameter> WorldState,
									   TMap<FName, FParameter> GoalState,
									   TQueue<UAction*>& OutPlan)
{
	UE_LOG(LogTemp, Warning, TEXT("Create plan"));
	// reset the actions so we can start fresh with them
	for (UAction* Action : AvailableActions)
	{
		Action->DoReset();
	}
	
	// check what actions can run using their checkProceduralPrecondition
	TSet<UAction*> UsableActions;
	for (UAction* Action : AvailableActions)
	{
		if (Action->CheckProceduralPrecondition(Agent))
		{
			UsableActions.Add(Action);
		}
	}

	// we now have all actions that can run, stored in usableActions
	// build up the tree and record the leaf nodes that provide a solution to the goal.
	TArray<FNode*> LeafNodes;

	// build graph
	auto Start = FNode(nullptr, 0, WorldState, nullptr);
	bool bSuccess = BuildGraph(&Start, LeafNodes, UsableActions, GoalState);

	if (!bSuccess)
	{
		// oh no, we didn't get a plan
		UE_LOG(LogTemp, Warning, TEXT("NO PLAN"));
		return false;
	}

	// get the cheapest leaf node
	FNode* Cheapest = nullptr;
	for (FNode* LeafNode : LeafNodes)
	{
		if (!Cheapest)
			Cheapest = LeafNode;
		else
		{
			if (LeafNode->RunningCost < Cheapest->RunningCost)
				Cheapest = LeafNode;
		}
	}
	// get its node and work back through the parents
	
	TArray<UAction*> Result;
	auto Node = Cheapest;
	while (Node)
	{
		if (Node && Node->Action)
		{
			Result.EmplaceAt(0, Node->Action); // insert the action in the front
		}
		Node = Node->Parent;
	}
	// we now have this action list in correct order
	
	for (UAction* Action : Result)
	{
		OutPlan.Enqueue(Action);
	}
	// hooray we have a plan!
	
	return true;
}

bool UActionPlanner::BuildGraph(FNode* ParentNode, TArray<FNode*>& LeafNodes, TSet<UAction*>& UsableActions, TMap<FName, FParameter>& GoalState)
{
	bool bFoundOne = false;
	// go through each action available at this node and see if we can use it here
	for (auto Action : UsableActions)
	{
		// if the parent state has the conditions for this action's preconditions, we can use it here
		if(InState(Action->Preconditions, ParentNode->State))
		{
			// apply the action's effects to the parent state
			TMap<FName, FParameter> AppliedState = ApplyState(Action->Effects, ParentNode->State);

			// if we reached goal state, return leaves
			if(InState(GoalState, AppliedState))
			{
				FNode NewNode(ParentNode, ParentNode->RunningCost + Action->GetCost(), AppliedState, Action);
				LeafNodes.Add(&NewNode);
				bFoundOne = true;
			}
			// test all the remaining actions and branch out the tree
			else
			{
				auto SubActionSet = SubsetActions(UsableActions, Action);
				FNode NewNode(ParentNode, ParentNode->RunningCost + Action->GetCost(), AppliedState, Action);
				bFoundOne = BuildGraph(&NewNode, LeafNodes, SubActionSet, GoalState);				
			}
		}
	}
	return bFoundOne;
}

bool UActionPlanner::InState(const TMap<FName, FParameter>& Test, const TMap<FName, FParameter>& Target)
{
	// CHANGED: Matching differently
	for (const TTuple<FName, FParameter> Condition : Test)
	{
		if(const FParameter* Result = Target.Find(Condition.Key))
		{
			if(*Result == Condition.Value)
			{
				// move on to check the next condition only if this one matches
				continue;
			}
			// element found but no match
			return false;
		}
		// if not found
		return false;
	}
	// reach here only if all found and matched
	return true;
}

TMap<FName, FParameter> UActionPlanner::ApplyState(const TMap<FName, FParameter>& Source, TMap<FName, FParameter> Destination)
{
	// for all source conditions
	for (auto Param : Source)
	{
		Destination[Param.Key] = Param.Value;
		//if found condition, update the value
		if(FParameter* Result = Destination.Find(Param.Key))
		{
			*Result = Param.Value;
			continue;
		}
		//else add it to the state
		Destination.Add(Param);
	}
	return Destination;
}

TSet<UAction*> UActionPlanner::SubsetActions(TSet<UAction*>& ActionSet, const UAction* RemoveAction)
{
	ActionSet.Remove(RemoveAction);
	return ActionSet;
}