// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EParamType : uint8
{
	EPT_None = 0	UMETA(DisplayName = "Undefined"),
	EPT_Bool = 1	UMETA(DisplayName = "Bool"),
	EPT_Int = 2		UMETA(DisplayName = "Int"),
	EPT_Float = 3	UMETA(DisplayName = "Float"),
};

/*
 * 
 */
class ACTIONPLANNING_API FParameter
{
public:
	explicit FParameter(const bool Val);

	explicit FParameter(const int32 Val);

	explicit FParameter(const float Val);

	bool bVal;
	int32 iVal;
	float fVal;

	int32 GetIntValue() const	{ return iVal; }
	float GetFloatValue() const { return fVal; }
	bool GetBoolValue() const	{ return bVal; }

	EParamType GetParamType() const { return ParamType; }

	bool operator<(const FParameter& Other) const;

	bool operator>(const FParameter& Other) const;

	// returns true if param type and value is same, will return true for different objects too
	bool operator==(const FParameter& Other) const;

	FString ToString() const;

private:
	FParameter();

	EParamType ParamType;
};
