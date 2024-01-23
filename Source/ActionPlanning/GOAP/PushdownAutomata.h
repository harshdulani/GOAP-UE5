#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PushdownAutomata.generated.h"

class UIdleState;
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

	UPROPERTY()
	UIdleState* IdleState;
};
