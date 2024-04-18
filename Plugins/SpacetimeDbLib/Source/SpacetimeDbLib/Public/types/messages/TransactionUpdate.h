// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SubscriptionUpdate.h"
#include "nlohmann/json.hpp"

#include "TransactionUpdate.generated.h"

USTRUCT(BlueprintType)
struct SPACETIMEDBLIB_API FTransactionUpdate
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	FSubscriptionUpdate SubscriptionUpdate;
	
	static FTransactionUpdate Build(nlohmann::basic_json<> json)
	{
		FTransactionUpdate transactionUpdate;
		
		// build subscription updates
		transactionUpdate.SubscriptionUpdate = FSubscriptionUpdate::Build(json["subscription_update"]);
		
		return transactionUpdate;
	}
	
};
