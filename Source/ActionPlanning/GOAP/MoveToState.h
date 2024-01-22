// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "State.h"
#include "MoveToState.generated.h"

UCLASS()
class ACTIONPLANNING_API UMoveToState : public UState
{
	GENERATED_BODY()

public:
	
	bool Execute() override;
	
	void Initialise(ACharacter* Character, FVector Destination);
	
	float GetDistanceToDestination() const;
	
private:

public:

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = true))
	ACharacter* Agent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = true))
	FVector Destination;
	
};
