
#include "Action.h"

UAction::UAction()
{
}

UAction::~UAction()
{
	Preconditions.Empty();
	Effects.Empty();
}

void UAction::AddPrecondition(FString Name, TUnion<int, float, bool> Value)
{
	Preconditions.Add(TPairInitializer(Name, Value));
}

void UAction::AddEffect(FString Name, TUnion<int, float, bool> Value)
{
	Effects.Add(TPairInitializer(Name, Value));
}
