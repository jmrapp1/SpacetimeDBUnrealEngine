// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "TableUpdate.h"

#include "SubscriptionUpdate.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct SPACETIMEDBLIB_API FSubscriptionUpdate
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	TArray<FTableUpdate> TableUpdates;

	static FSubscriptionUpdate Build(TSharedPtr<FJsonObject> json)
	{
		FSubscriptionUpdate subscriptionUpdate;

		// get table updates array
		auto tableUpdatesJson = json->GetArrayField("table_updates");

		// build table updates
		for (TSharedPtr<FJsonValue> updateJson : tableUpdatesJson)
		{
			subscriptionUpdate.TableUpdates.Push(FTableUpdate::Build(updateJson->AsObject()));
		}

		return subscriptionUpdate;
	}
};
