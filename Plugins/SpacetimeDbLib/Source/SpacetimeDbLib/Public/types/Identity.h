// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Identity.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct SPACETIMEDBLIB_API FIdentity
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	FString Identity;

	UPROPERTY(BlueprintReadWrite)
	FString Token;
	
	UPROPERTY(BlueprintReadWrite)
	FString Address;
};
