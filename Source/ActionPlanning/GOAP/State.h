// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "State.generated.h"

UCLASS(Abstract, Blueprintable)
class ACTIONPLANNING_API UState : public UObject
{
	GENERATED_BODY()
public:
	
	// Return true if should stay inside this state, false if should exit
	virtual bool Execute()
	PURE_VIRTUAL(UState::Execute, return true;);

	virtual void Print();
	
public:
};
