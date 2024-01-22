// Fill out your copyright notice in the Description page of Project Settings.
#include "PushdownAutomata.h"
#include "GameFramework/Character.h"
#include "MoveToState.h"
#include "State.h"

// Sets default values for this component's properties
UPushdownAutomata::UPushdownAutomata()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	
}

UPushdownAutomata::~UPushdownAutomata()
{
	StateStack.Empty();
}

// Called when the game starts
void UPushdownAutomata::BeginPlay()
{
	Super::BeginPlay();

	// Add idle state to stack
	
}


// Called every frame
void UPushdownAutomata::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// if success in executing state, return
	if(StateStack.Top()->Execute())
	{
		return;
	}

	// if failed/ finished the state, pop
	StateStack.Pop();
}

float UPushdownAutomata::PushNewMoveState(ACharacter* Character, FVector Location)
{
	UMoveToState* NewState = NewObject<UMoveToState>();
	NewState->Initialise(Character, Location);
	StateStack.Push(NewState);
	return NewState->GetDistanceToDestination();
}

