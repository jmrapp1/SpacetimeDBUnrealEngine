// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TableRowUpdate.generated.h"


USTRUCT(BlueprintType)
struct SPACETIMEDBLIB_API FTableRowUpdate
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	FString BeforeUpdateJson;

	UPROPERTY(BlueprintReadWrite)
	FString AfterUpdateJson;
	
};
