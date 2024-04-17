// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AlgebraicType.generated.h"

/**
 * https://github.com/clockworklabs/spacetimedb-typescript-sdk/blob/main/src/algebraic_type.ts#L143
 */
UENUM(BlueprintType)
enum class AlgebraicType : uint8
{
	STRING UMETA(DisplayName = "String"),
	INT UMETA(DisplayName = "Integer"),
	FLOAT UMETA(DisplayName = "Float"),
	BOOLEAN UMETA(DisplayName = "Boolean"),
	ARRAY UMETA(DisplayName = "Array"),
	MAP UMETA(DisplayName = "Map"),
};
