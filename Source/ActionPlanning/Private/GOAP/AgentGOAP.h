// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Action.h"
#include "GameFramework/Character.h"
#include "AgentGOAP.generated.h"

class UBackpackComponent;
class UActionPlanner;
class UPushdownAutomata;

class ACTIONPLANNING_API IGoapable
{
protected:
	~IGoapable() = default;

public:
	/**
	 * The starting state of the Agent and the world.
	 * Supply what states are needed for actions to run.
	 */
	virtual TMap<FName, FParameter> GetCurrentState()
	PURE_VIRTUAL(IGoapable::GetCurrentState, return TMap<FName, FParameter>(););
	
	/**
		 * Give the planner a new goal so it can figure out 
		 * the actions needed to fulfill it.
		 */
	virtual TMap<FName, FParameter> GetGoalState()
	PURE_VIRTUAL(IGoapable::GetGoalState, return TMap<FName, FParameter>(););

	/**
     * No sequence of actions could be found for the supplied goal.
     * You will need to try another goal
     */
    virtual void OnPlanFailed(TMap<FName, FParameter> FailedGoal)
	PURE_VIRTUAL(IGoapable::OnPlanFailed, );

    /**
     * A plan was found for the supplied goal.
     * These are the actions the Agent will perform, in order.
     */
    virtual void OnPlanFound(TMap<FName, FParameter> GoalState, TQueue<UAction*> Actions)
	PURE_VIRTUAL(IGoapable::OnPlanFound, );

    /**
     * All actions are complete and the goal was reached. Hooray!
     */
    virtual void OnPlanSuccess()
	PURE_VIRTUAL(IGoapable::OnPlanSuccess, );

    /**
     * One of the actions caused the plan to abort.
     * That action is returned.
     */
    virtual void OnPlanAborted(UAction* AbortAction)
	PURE_VIRTUAL(IGoapable::OnPlanAborted, );

    /**
     * Called during Update. Move the agent towards the target in order
     * for the next action to be able to perform.
     * Return true if the Agent is at the target and the next action can perform.
     * False if it is not there yet.
     */
    virtual bool MoveTo(UAction* NextAction)
	PURE_VIRTUAL(IGoapable::MoveTo, return true;);
};

UCLASS()
class ACTIONPLANNING_API AAgentGOAP : public ACharacter, public IGoapable
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAgentGOAP();
	
	//Interface overrides
	virtual TMap<FName, FParameter> GetCurrentState() override;
	virtual TMap<FName, FParameter> GetGoalState() override;
	virtual void OnPlanFailed(TMap<FName, FParameter> FailedGoal) override;
	virtual void OnPlanFound(TMap<FName, FParameter> GoalState, TQueue<UAction*> Actions) override;
	virtual void OnPlanSuccess() override;
	virtual void OnPlanAborted(UAction* AbortAction) override;
	virtual bool MoveTo(UAction* NextAction) override;

private:
	static FString StateToString(const TMap<FName, FParameter>& State);
	
private:	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = true))
	UPushdownAutomata* Fsm;

	UPROPERTY(VisibleAnywhere, meta=(AllowPrivateAccess = true))
	UActionPlanner* ActionPlanner;
	
	UPROPERTY(VisibleAnywhere, meta=(AllowPrivateAccess = true))
	UBackpackComponent* Backpack;
};
