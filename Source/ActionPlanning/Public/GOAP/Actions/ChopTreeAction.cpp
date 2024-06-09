// Fill out your copyright notice in the Description page of Project Settings.
#include "GOAP/Actions/ChopTreeAction.h"
#include "NavigationPath.h"
#include "NavigationSystem.h"
#include "FParameter.h"
#include "GOAP/AgentGOAP.h"
#include "Kismet/GameplayStatics.h"

UChopTreeAction::UChopTreeAction()
{
	bIsInRange = false;
	bChoppingDone = false;
	WorkDuration = 2.f; // seconds
	StartTime = -1.f;
	
	AddPrecondition("HasTool", FParameter(true)); // we need a tool to do this
	AddPrecondition("HasLogs", FParameter(false)); // if we have logs we don't want more
	AddEffect("HasLogs", FParameter(true));
}

void UChopTreeAction::DoReset()
{
	Super::DoReset();
	bIsInRange = false;
	bChoppingDone = false;
	WorkDuration = 2.f; // seconds
	StartTime = -1.f;
}

int UChopTreeAction::GetCost()
{
	// maybe path cost + work duration
	return PathCost;
}

bool UChopTreeAction::CheckProceduralPrecondition(AAgentGOAP* Agent)
{
	const auto NavSystem = UNavigationSystemV1::GetCurrent(Agent);
	// find "trees"
	TArray<AActor*> Trees;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("Tree"), Trees);

	if(Trees.Num() == 0)
	{
		return false;
	}

	AActor* Closest = Trees[0];

	float LeastPathCost = NavSystem->FindPathToActorSynchronously(Agent, Agent->GetActorLocation(), Trees[0])
									 ->GetPathCost();
	
	// choose closest
	for(int32 i = 1; i < Trees.Num(); ++i)
	{
		if(const float PathCostTest = NavSystem->FindPathToActorSynchronously(Agent, Agent->GetActorLocation(), Trees[i])->GetPathCost();
			PathCostTest < LeastPathCost)
		{
			Closest = Trees[i];
			LeastPathCost = PathCostTest;
		}
	}

	Target = Closest;
	PathCost = LeastPathCost;
	return true;
}

void UChopTreeAction::Print()
{
	UE_LOG(LogTemp, Log, TEXT("Print: TestAction - Chop Tree"));
}

bool UChopTreeAction::Perform()
{
	Super::Perform();
	UE_LOG(LogTemp, Log, TEXT("Perform : TestAction - Chop Tree"));

	if(StartTime == -1)
	{
		StartTime = UGameplayStatics::GetRealTimeSeconds(Target);
		return false;
	}
	if(StartTime + WorkDuration >= UGameplayStatics::GetRealTimeSeconds(Target))
	{
		return false;
	}	
	bChoppingDone = true;
	return true;
}

int UChopTreeAction::IsDone()
{
	return bChoppingDone;
}
