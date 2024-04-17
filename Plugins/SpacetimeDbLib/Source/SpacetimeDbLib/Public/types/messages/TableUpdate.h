// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TableRowOperation.h"

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

	static FTableUpdate Build(TSharedPtr<FJsonObject> json)
	{
		FTableUpdate tableUpdate;
		tableUpdate.TableId = json->GetIntegerField("table_id");
		tableUpdate.TableName = json->GetStringField("table_name");

		// add row ops
		auto rowOpsJson = json->GetArrayField("table_row_operations");
		for (TSharedPtr<FJsonValue> rowOp : rowOpsJson)
		{
			tableUpdate.TableRowOperations.Push(FTableRowOperation::Build(rowOp->AsObject()));
		}
		
		return tableUpdate;
	}
};
