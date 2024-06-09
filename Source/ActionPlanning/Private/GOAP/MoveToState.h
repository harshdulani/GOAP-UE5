// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "State.h"
#include "MoveToState.generated.h"

class UNavigationPath;

UCLASS()
class ACTIONPLANNING_API UMoveToState : public UState
{
	GENERATED_BODY()

public:
	UMoveToState();
	
	virtual bool Execute(const float DeltaTime) override;
	
	UFUNCTION(BlueprintCallable)
	void InitialiseLocation(ACharacter* Character, const FVector& Destination);

	UFUNCTION(BlueprintCallable)
	void InitialiseActor(ACharacter* Character, AActor* Destination);

	UFUNCTION(BlueprintCallable)
	float GetDistanceToDestination() const { return PathLength; }
	
private:
	bool IncreasePathPointIndex();
	
public:

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = true))
	ACharacter* Agent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = true))
	FVector DestinationLocation;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = true))
	AActor* DestinationActor;
	
	// Pathfinding
	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess = true))
	UNavigationPath* NavPath;
	
	TArray<FNavPathPoint> PathPoints;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = true))
	float TetherDistance;

	int32 LastPointIndex;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = true))
	float MoveSpeed;

	FVector NextPointLocation;
	FVector CurrentNormal;
	FRotator CurrentNormalRotator;

	float PathLength;
};
