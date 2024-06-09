// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "FParameter.h"
#include "Action.generated.h"

ACTIONPLANNING_API DECLARE_LOG_CATEGORY_EXTERN(LogGOAP_Action, Log, All);

class AAgentGOAP;
//class FParameter;
class AActionPlanningCharacter;

UCLASS(Abstract, Blueprintable)
class ACTIONPLANNING_API UAction : public UObject
{
	GENERATED_BODY()
public:
	UAction();
	virtual ~UAction() override;
	
	virtual void DoReset()
	PURE_VIRTUAL(UAction::DoReset, );
	
	virtual int GetCost()
	PURE_VIRTUAL(UAction::GetCost, return -1;)
		
	virtual bool CheckProceduralPrecondition(AAgentGOAP* Agent)
	PURE_VIRTUAL(UAction::CheckProceduralPrecondition, return false;);
	
	virtual int IsDone()
	PURE_VIRTUAL(UAction::IsDone, return false;)
	
	virtual bool Perform()
	PURE_VIRTUAL(UAction::Perform, return false;);

	virtual void Print()
	PURE_VIRTUAL(UAction::Print, );
	
	void AddPrecondition(FName Name, const FParameter& Value);
	void AddEffect(FName Name, const FParameter& Value);

	void SetIsInRange(const bool& bInRange) { bIsInRange = bInRange; }

	bool IsInRange() const { return bIsInRange; }
		
public:
	TMap<FName, FParameter> Preconditions;
	TMap<FName, FParameter> Effects;

	// Target on which Action is to be performed
	UPROPERTY(VisibleAnywhere)
	AActor* Target;
	
protected:
	bool bIsInRange;
};
