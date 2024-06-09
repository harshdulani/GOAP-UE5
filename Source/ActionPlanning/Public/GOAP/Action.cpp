
#include "GOAP/Action.h"
#include "FParameter.h"

DEFINE_LOG_CATEGORY(LogGOAP_Action);

UAction::UAction()
	: Target(nullptr),
	  bIsInRange(false)
{
}

UAction::~UAction()
{
	Preconditions.Empty();
	Effects.Empty();
}

void UAction::AddPrecondition(const FName Name, const FParameter& Value)
{
	Preconditions.Emplace(Name, Value);
}

void UAction::AddEffect(const FName Name, const FParameter& Value)
{
	Effects.Emplace(Name, Value);
}
