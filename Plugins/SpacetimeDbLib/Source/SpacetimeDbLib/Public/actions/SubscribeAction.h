#pragma once

#include "nlohmann/json.hpp"

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
		auto queriesJson = nlohmann::json::array({});
		for (FString query : queries)
		{
			queriesJson.push_back(Utils::ToString(query));
		}

		nlohmann::json json = {
			{"subscribe", {
					{"query_strings", queriesJson}
				}
			}
		};
		return json.dump();
	}
};
