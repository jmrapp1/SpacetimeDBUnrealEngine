// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MessageReceivedEvent.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct SPACETIMEDBLIB_API FMessageReceivedEvent
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	FString Payload;
};
