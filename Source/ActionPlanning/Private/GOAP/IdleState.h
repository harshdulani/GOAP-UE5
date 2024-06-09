// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "State.h"
#include "IdleState.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONPLANNING_API UIdleState : public UState
{
	GENERATED_BODY()

public:
	bool Execute(const float DeltaTime) override;
};
