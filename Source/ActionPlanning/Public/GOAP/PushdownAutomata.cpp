// Fill out your copyright notice in the Description page of Project Settings.
#include "GOAP/PushdownAutomata.h"
#include "GOAP/IdleState.h"
#include "GameFramework/Character.h"
#include "GOAP/MoveToState.h"
#include "GOAP/State.h"

// Sets default values for this component's properties
UPushdownAutomata::UPushdownAutomata()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	IdleState = CreateDefaultSubobject <UIdleState>(TEXT("IdleState"));
}

UPushdownAutomata::~UPushdownAutomata()
{
	StateStack.Empty();
	IdleState = nullptr;
}

// Called when the game starts
void UPushdownAutomata::BeginPlay()
{
	Super::BeginPlay();

	// Add idle state to stack
	StateStack.Push(IdleState);
}

// Called every frame
void UPushdownAutomata::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	const auto State = StateStack.Top();
	FString StateName("IdleState");
	if(!Cast<UIdleState>(State))
	{
		if(Cast<UMoveToState>(State))
		{
			StateName = "MoveToState";
		}
		else
		{
			StateName = "Invalid";
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("State = %s"), *StateName);
	// if success in executing state, return
	if(State->Execute(DeltaTime))
	{
		return;
	}

	// if failed/ finished the state, pop
	StateStack.Pop();
}

float UPushdownAutomata::PushNewMoveState(ACharacter* Character, FVector Location)
{
	UMoveToState* NewState = NewObject<UMoveToState>();
	NewState->InitialiseLocation(Character, Location);
	StateStack.Push(NewState);
	return NewState->GetDistanceToDestination();
}