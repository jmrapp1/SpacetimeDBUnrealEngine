// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EntityComponent.generated.h"

USTRUCT(BlueprintType)
struct  TOPDOWNPROJECT_API FEntityComponent
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadWrite)
	int Id;
	
	UPROPERTY(BlueprintReadWrite)
	FVector3f Position;
	
	UPROPERTY(BlueprintReadWrite)
	FRotator3f Rotation;
	
	UPROPERTY(BlueprintReadWrite)
	FVector3f Velocity;
	
	UPROPERTY(BlueprintReadWrite)
	bool Moving;
};
