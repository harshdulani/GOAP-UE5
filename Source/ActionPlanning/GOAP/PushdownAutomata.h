#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PushdownAutomata.generated.h"

class UState;

UCLASS( ClassGroup=(GOAP), meta=(BlueprintSpawnableComponent) )
class ACTIONPLANNING_API UPushdownAutomata : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPushdownAutomata();
	~UPushdownAutomata();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	float PushNewMoveState(ACharacter* Character, FVector Location);
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = true))
	TArray<UState*> StateStack;
	
	/*
	private static readonly IdleState IdleState = new IdleState();

	private void Start()
	{
		Stack.Push(IdleState);
	}

	public static float CreateMoveState(AgentController agent, Vector3 position)
	{
		var moveState = new MoveState(agent, position);
		Stack.Push(moveState);
		return moveState.GetDistanceToDest();
	}
	*/
};
