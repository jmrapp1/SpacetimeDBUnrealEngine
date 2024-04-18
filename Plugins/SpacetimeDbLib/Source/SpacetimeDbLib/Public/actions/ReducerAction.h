#pragma once

#include "nlohmann/json.hpp"

struct ReducerAction
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
	static std::string BuildReducerAction(std::string reducerName, nlohmann::basic_json<> args)
	{
		nlohmann::json reducerJson = {
			{
				"call", {
					{"fn", reducerName},
					{"args", args}
				}
			}
		};
		return reducerJson.dump();
	}
};
