// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "FPlayerStruct.generated.h"

/**
 * Cant name Player because of confliction with UE's Player
 */
USTRUCT(BlueprintType)
struct TOPDOWNPROJECT_API FPlayerStruct
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadWrite)
	FString Identity;
	
	UPROPERTY(BlueprintReadWrite)
	FString Name;
	
	UPROPERTY(BlueprintReadWrite)
	int EntityComponentId;

	UPROPERTY(BlueprintReadWrite)
	bool Online;
};
