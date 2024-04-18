// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TableRowOperation.h"
#include "nlohmann/json.hpp"

#include "TableUpdate.generated.h"

USTRUCT(BlueprintType)
struct SPACETIMEDBLIB_API FTableUpdate
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	int TableId;

	UPROPERTY(BlueprintReadWrite)
	FString TableName;

	UPROPERTY(BlueprintReadWrite)
	TArray<FTableRowOperation> TableRowOperations;

	UPROPERTY(BlueprintReadWrite)
	bool UpdateOperation;
	
	UPROPERTY(BlueprintReadWrite)
	FString BeforeUpdateJson;

	UPROPERTY(BlueprintReadWrite)
	FString AfterUpdateJson;

	static FTableUpdate Build(nlohmann::basic_json<> json)
	{
		FTableUpdate tableUpdate;
		tableUpdate.TableId = json["table_id"].get<int>();
		tableUpdate.TableName = Utils::ToFString(json["table_name"].get<std::string>());

		// add row ops
		auto rowOpsJson = json["table_row_operations"];
		for (auto& rowOp : rowOpsJson)
		{
			tableUpdate.TableRowOperations.Push(FTableRowOperation::Build(rowOp));
		}
		
		return tableUpdate;
	}
};
