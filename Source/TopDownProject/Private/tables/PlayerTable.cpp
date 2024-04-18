// Fill out your copyright notice in the Description page of Project Settings.

#include "tables/PlayerTable.h"

/**
 *	Example User JSON
	* [
	   [
		  "f88d6dc04ee40fab452d7fcfc89db658773c4acd0c941827861d0b024cd27da6"
	   ],
	   {
		  "0":"jrapp"
	   },
	   true
	]
 * 
 */
FPlayerStruct UPlayerTable::DeserializePlayer(FString playerJsonStr)
{
	auto playerJson = nlohmann::json::parse(Utils::ToString(playerJsonStr));
	
	FPlayerStruct player;
	player.Identity = Utils::ToFString(playerJson[0][0].get<std::string>());

	// Read name
	if (playerJson[1].contains("0"))
	{
		player.Name = Utils::ToFString(playerJson[1]["0"].get<std::string>());
	}

	player.Online = playerJson[2].get<bool>();
	player.EntityComponentId = playerJson[3].get<int>();
	
	return player;
}

bool UPlayerTable::IsLocalPlayer(FIdentity Identity, FPlayerStruct Player)
{
	return Player.Identity == Identity.Identity;
}

UStdbPlayerComponent* UPlayerTable::FilterPlayerComponentsById(FString Id, TArray<UStdbPlayerComponent*> Players)
{
	for (UStdbPlayerComponent* player : Players)
	{
		if (player->Player.Identity == Id)
		{
			return player;
		}
	}
	return nullptr;
}

void UPlayerTable::UpdatePlayerPositionReducer(USpacetimeClientComponent* SpacetimeClient, FVector3f Position, FRotator3f Rotation, bool Moving)
{
	auto args = nlohmann::json::array({
		{
			Position.X,
			Position.Y,
			Position.Z
		},
		{
			Rotation.Pitch,
			Rotation.Yaw,
			Rotation.Roll
		},
		false
	});

	if (SpacetimeClient == nullptr) {
		Utils::LogError("SpacetimeClient was null when calling UpdatePlayerPosition reducer");
	} else {
		SpacetimeClient->InvokeReducer("update_player_position", args);
	}
}
