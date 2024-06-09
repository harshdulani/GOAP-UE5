// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BackpackComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTIONPLANNING_API UBackpackComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBackpackComponent();

public:
	UPROPERTY(BlueprintReadWrite)
	int32 FirewoodCount;
	UPROPERTY(BlueprintReadWrite)
	int32 LogCount;
	UPROPERTY(BlueprintReadWrite)
	int32 OreCount;
	UPROPERTY(BlueprintReadWrite)
	UObject* Tool;
	//UToolGOAP* WoodCount;
	
private:
};
