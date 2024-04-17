// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SubscriptionUpdate.h"

#include "TransactionUpdate.generated.h"

USTRUCT(BlueprintType)
struct SPACETIMEDBLIB_API FTransactionUpdate
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	FSubscriptionUpdate SubscriptionUpdate;
	
	static FTransactionUpdate Build(TSharedPtr<FJsonObject> json)
	{
		FTransactionUpdate transactionUpdate;
		
		// build subscription updates
		transactionUpdate.SubscriptionUpdate = FSubscriptionUpdate::Build(json->GetObjectField("subscription_update"));
		
		return transactionUpdate;
	}
	
};
