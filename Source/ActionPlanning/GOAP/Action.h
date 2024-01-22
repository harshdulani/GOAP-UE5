// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Action.generated.h"

UCLASS(Abstract, Blueprintable)
class ACTIONPLANNING_API UAction : public UObject
{
	GENERATED_BODY()
public:
	UAction();
	~UAction();
	
	virtual int GetCost()
	PURE_VIRTUAL(UAction::GetCost, return -1;);

	virtual bool CheckProceduralPrecondition()
	PURE_VIRTUAL(UAction::CheckProceduralPrecondition, return false;);

	virtual void Print()
	PURE_VIRTUAL(UAction::Print, );

	virtual void Perform()
	PURE_VIRTUAL(UAction::Perform, );
	
	void AddPrecondition(FString Name, TUnion<int, float, bool> Value);
	void AddEffect(FString Name, TUnion<int, float, bool> Value);
	
protected:
	
public:
	TSet<TPair<FString, TUnion<int, float, bool>>> Preconditions;
	TSet<TPair<FString, TUnion<int, float, bool>>> Effects;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Data")
	USceneComponent* Target;
	
protected:
};
