// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AlgebraicType.h"
#include "AlgebraicValue.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct SPACETIMEDBLIB_API FAlgebraicValue
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	FString Value;

	UPROPERTY(BlueprintReadWrite)
	AlgebraicType PropertyType;
};
