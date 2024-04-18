// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TableRowInsertion.h"
#include "TableRowUpdate.h"
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
	TArray<FTableRowInsertion> Insertions;

	UPROPERTY(BlueprintReadWrite)
	TArray<FTableRowUpdate> Updates;

	static FTableUpdate Build(nlohmann::basic_json<> json)
	{
		FTableUpdate tableUpdate;
		tableUpdate.TableId = json["table_id"].get<int>();
		tableUpdate.TableName = Utils::ToFString(json["table_name"].get<std::string>());

		// get row ops
		auto rowOpsJson = json["table_row_operations"];

		// check if its an update
		bool isUpdate = false;
		if (rowOpsJson.size() == 2)
		{
			auto firstRowOp = rowOpsJson[0]["op"].get<std::string>();
			auto secondRowOp = rowOpsJson[1]["op"].get<std::string>();
			if (firstRowOp == "insert" && secondRowOp == "delete")
			{
				FTableRowUpdate update;
				update.BeforeUpdateJson = Utils::ToFString(secondRowOp);
				update.AfterUpdateJson = Utils::ToFString(firstRowOp);
				tableUpdate.Updates.Push(update);
				isUpdate = true;
			}
			else if (firstRowOp == "delete" && secondRowOp == "insert")
			{
				FTableRowUpdate update;
				update.BeforeUpdateJson = Utils::ToFString(firstRowOp);
				update.AfterUpdateJson = Utils::ToFString(secondRowOp);
				tableUpdate.Updates.Push(update);
				isUpdate = true;
			}
		}

		if (!isUpdate)
		{
			for (auto& rowOp : rowOpsJson)
			{
				std::string op = rowOp["op"].get<std::string>();
				if (op == "insert")
				{
					tableUpdate.Insertions.Push(FTableRowInsertion::Build(rowOp));
				}
				else
				{
					Utils::LogError("Got a row update that was expected to be an insertion but wasnt");
					Utils::LogError(op);
					Utils::LogError(rowOp["row"].get<std::string>());
				}
			}
		}
		
		return tableUpdate;
	}
};
