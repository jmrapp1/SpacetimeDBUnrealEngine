// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TableRowOperation.generated.h"

USTRUCT(BlueprintType)
struct SPACETIMEDBLIB_API FTableRowOperation
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	FString Op;

	UPROPERTY(BlueprintReadWrite)
	FString RowJson;

	static FTableRowOperation Build(TSharedPtr<FJsonObject> json)
	{
		FTableRowOperation rowOperation;
		rowOperation.Op = json->GetStringField("op");
		rowOperation.RowJson = Utils::JsonToFString(json->GetArrayField("row"));

		return rowOperation;
	}
};
