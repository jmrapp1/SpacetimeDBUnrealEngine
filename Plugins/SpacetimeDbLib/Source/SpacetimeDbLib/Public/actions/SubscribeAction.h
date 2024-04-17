#pragma once

#include "Utils.h"

struct SubscribeAction
{
	/**
	 * Forms JSON in the following format according to Subscribe
	 * https://spacetimedb.com/docs/ws#subscribe
		{
			"subscribe": {
				"query_strings": array<string>
			}
		}
	 */
	static std::string BuildSubscribe(TArray<FString> queries)
	{
		TSharedPtr<FJsonObject> requestJson = MakeShareable(new FJsonObject);
		TSharedPtr<FJsonObject> subscribeJson = MakeShareable(new FJsonObject);
		TArray<TSharedPtr<FJsonValue>> queriesJson;

		for (FString query : queries)
		{
			queriesJson.Add(MakeShareable(new FJsonValueString(query)));
		}
		
		subscribeJson->SetArrayField("query_strings", queriesJson);
		requestJson->SetObjectField("subscribe", subscribeJson);
		return Utils::ToString(Utils::JsonToFString(requestJson));
	}

	
};
