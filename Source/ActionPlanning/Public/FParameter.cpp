#include "FParameter.h"

FParameter::FParameter()
		: bVal(false),
		  iVal(-1),
		  fVal(-1.f),
		  ParamType(EParamType::EPT_None)
{
	ensureMsgf(true, TEXT("Invalid FParameter created"));
}

FParameter::FParameter(const bool Val): bVal(Val),
										iVal(-1),
										fVal(-1.f),
										ParamType(EParamType::EPT_Bool)
{
}

FParameter::FParameter(const int32 Val): bVal(false),
										 iVal(Val),
										 fVal(-1.f),
										 ParamType(EParamType::EPT_Int)
{
}

FParameter::FParameter(const float Val): bVal(false),
										 iVal(-1),
										 fVal(-Val),
										 ParamType(EParamType::EPT_Float)
{
}

bool FParameter::operator<(const FParameter& Other) const
{
	if (Other.ParamType != this->ParamType)
	{
		return false;
	}
	switch (ParamType)
	{
		case EParamType::EPT_Bool:
			return false;
		case EParamType::EPT_Int:
			return iVal < Other.iVal;
		case EParamType::EPT_Float:
			return fVal < Other.fVal;
		case EParamType::EPT_None:
		default:
			return false;
	}
}

bool FParameter::operator>(const FParameter& Other) const
{
	if (Other.ParamType != this->ParamType)
	{
		return false;
	}
	switch (ParamType)
	{
		case EParamType::EPT_Bool:
			return false;
		case EParamType::EPT_Int:
			return iVal > Other.iVal;
		case EParamType::EPT_Float:
			return fVal > Other.fVal;
		case EParamType::EPT_None:
		default:
			return false;
	}
}

bool FParameter::operator==(const FParameter& Other) const
{
	if (Other.ParamType != this->ParamType)
	{
		return false;
	}
	switch (ParamType)
	{
		case EParamType::EPT_Bool:
			return bVal == Other.bVal;
		case EParamType::EPT_Int:
			return iVal == Other.iVal;
		case EParamType::EPT_Float:
			return fVal == Other.fVal;
		case EParamType::EPT_None:
		default:
			return false;
	}
}

FString FParameter::ToString() const
{
	switch (ParamType)
	{
		case EParamType::EPT_Bool:
			return bVal ? "True" : "False";
		case EParamType::EPT_Int:
			return FString::FromInt(iVal);
		case EParamType::EPT_Float:
			return FString::SanitizeFloat(fVal);
		case EParamType::EPT_None:
		default:
		return "";
	}	
}
