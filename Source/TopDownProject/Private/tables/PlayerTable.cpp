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
	auto playerJson = Utils::ParseJsonArray(Utils::ToString(playerJsonStr));
	
	FPlayerStruct player;
	player.Identity = playerJson[0]->AsArray()[0]->AsString();

	// Read name
	auto name = jsonObjectAdapter.ReadSome(playerJson[1]->AsObject(), AlgebraicType::STRING);
	if (name.IsSet)
	{
		player.Name = name.String;
	}

	player.Online = playerJson[2]->AsBool();
	player.EntityComponentId = playerJson[3]->AsNumber();
	
	return player;
}

TArray<FPlayerStruct> UPlayerTable::DeserializePlayers(TArray<FString> playerJsons)
{
	TArray<FPlayerStruct> arr;
	for (FString jsonStr : playerJsons)
	{
		arr.Push(DeserializePlayer(jsonStr));
	}
	return arr;
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
