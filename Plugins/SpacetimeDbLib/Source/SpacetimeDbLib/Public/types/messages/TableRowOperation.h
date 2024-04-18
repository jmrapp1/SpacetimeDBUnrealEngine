// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "nlohmann/json.hpp"

#include "TableRowOperation.generated.h"

USTRUCT(BlueprintType)
struct SPACETIMEDBLIB_API FTableRowOperation
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	FString Op;

	UPROPERTY(BlueprintReadWrite)
	FString RowJson;

	static FTableRowOperation Build(nlohmann::basic_json<> json)
	{
		FTableRowOperation rowOperation;
		rowOperation.Op = Utils::ToFString(json["op"].get<std::string>());
		rowOperation.RowJson = Utils::ToFString(json["row"].dump());

		return rowOperation;
	}
};
