// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TableValue.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct SPACETIMEDBLIB_API FTableValue
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	FString String;

	UPROPERTY(BlueprintReadWrite)
	int Int;
	
	UPROPERTY(BlueprintReadWrite)
	bool Bool;

	UPROPERTY(BlueprintReadWrite)
	float Float;

	bool IsSet;
};
