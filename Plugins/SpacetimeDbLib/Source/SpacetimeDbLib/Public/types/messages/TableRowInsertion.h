// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "nlohmann/json.hpp"
#include "SpacetimeDbLib/Public/Utils.h"

#include "TableRowInsertion.generated.h"

USTRUCT(BlueprintType)
struct SPACETIMEDBLIB_API FTableRowInsertion
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	FString RowJson;

	static FTableRowInsertion Build(nlohmann::basic_json<> json)
	{
		FTableRowInsertion rowOperation;
		rowOperation.RowJson = Utils::ToFString(json["row"].dump());

		return rowOperation;
	}
};
