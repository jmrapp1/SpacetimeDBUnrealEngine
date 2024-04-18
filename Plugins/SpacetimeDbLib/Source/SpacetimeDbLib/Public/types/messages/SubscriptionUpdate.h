// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "TableUpdate.h"
#include "nlohmann/json.hpp"

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

	static FSubscriptionUpdate Build(nlohmann::basic_json<> json)
	{
		FSubscriptionUpdate subscriptionUpdate;

		// get table updates array
		nlohmann::json tableUpdatesJson = json["table_updates"];

		// build table updates
		for (auto& updateJson : tableUpdatesJson)
		{
			subscriptionUpdate.TableUpdates.Push(FTableUpdate::Build(updateJson));
		}

		return subscriptionUpdate;
	}
};
