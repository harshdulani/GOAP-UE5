// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GOAP/Action.h"
#include "ChopTreeAction.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONPLANNING_API UChopTreeAction : public UAction
{
	GENERATED_BODY()
	
public:
	UChopTreeAction();
	
	virtual void DoReset() override;
	
	virtual int GetCost() override;

	virtual bool CheckProceduralPrecondition(AAgentGOAP* Agent) override;

	virtual bool Perform() override;

	virtual int IsDone() override;

	virtual void Print() override;
	
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	float PathCost;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	float WorkDuration;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	bool bChoppingDone;

	float StartTime;
};
