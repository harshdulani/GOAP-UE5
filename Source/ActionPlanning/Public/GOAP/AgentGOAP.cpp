// Fill out your copyright notice in the Description page of Project Settings.

#include "GOAP/AgentGOAP.h"
#include "GOAP/PushdownAutomata.h"
#include "GOAP/ActionPlanner.h"
#include "GOAP/BackpackComponent.h"
#include "GOAP/Action.h"
#include "GOAP/MoveToState.h"

// Sets default values
AAgentGOAP::AAgentGOAP()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// GOAP
	Fsm = CreateDefaultSubobject<UPushdownAutomata>(TEXT("State Machine"));
	ActionPlanner = CreateDefaultSubobject<UActionPlanner>(TEXT("Planner"));
	Backpack = CreateDefaultSubobject<UBackpackComponent>(TEXT("BackPack"));	
}

TMap<FName, FParameter> AAgentGOAP::GetCurrentState()
{
	TMap<FName, FParameter> State;
	State.Emplace("HasLogs", Backpack->LogCount > 0);
	State.Emplace("HasOre", Backpack->OreCount > 0);
	State.Emplace("HasFirewood", Backpack->FirewoodCount > 0);
	State.Emplace("HasTool", Backpack->Tool != nullptr);
	return State;
}

TMap<FName, FParameter> AAgentGOAP::GetGoalState()
{
	TMap<FName, FParameter> State;
	State.Emplace("HasLogs", Backpack->LogCount > 0);
	State.Emplace("HasOre", Backpack->OreCount > 0);
	State.Emplace("HasFirewood", Backpack->FirewoodCount > 0);
	State.Emplace("HasTool", Backpack->Tool != nullptr);
	return State;
}

void AAgentGOAP::OnPlanFailed(TMap<FName, FParameter> FailedGoal)
{
	UE_LOG(LogGOAP_Action, Warning, TEXT("Plan Failed for %s"), *GetName());
}

void AAgentGOAP::OnPlanFound(TMap<FName, FParameter> GoalState, TQueue<UAction*> Actions)
{
	UE_LOG(LogGOAP_Action, Warning, TEXT("Plan Found for %s"), *GetName());
}

void AAgentGOAP::OnPlanSuccess()
{
	UE_LOG(LogGOAP_Action, Warning, TEXT("Plan Complete for %s"), *GetName());
}

void AAgentGOAP::OnPlanAborted(UAction* AbortAction)
{
	UE_LOG(LogGOAP_Action, Warning, TEXT("Plan Complete for %s"), *GetName());
}

bool AAgentGOAP::MoveTo(UAction* NextAction)
{
	UMoveToState* MoveToState = CreateDefaultSubobject<UMoveToState>(TEXT("MoveToState"));
	MoveToState->InitialiseActor(this, NextAction->Target);
	return false;
}

FString AAgentGOAP::StateToString(const TMap<FName, FParameter>& State)
{
	FString Out;
	for (auto& Param : State)
	{
		Out += Param.Key.ToString() + " = " + Param.Value.ToString() + "\n";
	}
	return Out;
}
