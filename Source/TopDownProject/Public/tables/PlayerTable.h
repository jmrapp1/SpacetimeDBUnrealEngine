// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "structs/FPlayerStruct.h"
#include "SpacetimeDbLib/Public/Utils.h"
// #include "SpacetimeDbLib/Public/SpacetimeClientComponent.h"
#include "types/Identity.h"
#include "components/StdbPlayerComponent.h"
#include "components/SpacetimeClientComponent.h"
#include "nlohmann/json.hpp"

#include "PlayerTable.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNPROJECT_API UPlayerTable : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Deserialize Player", Keywords = "Spacetime Player Deserialize"), Category = "SpacetimeDbLib")
	static FPlayerStruct DeserializePlayer(FString PlayerJson);
	
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Is Local Player", Keywords = "Spacetime Is Local Player"), Category = "SpacetimeDbLib")
	static bool IsLocalPlayer(FIdentity Identity, FPlayerStruct Player);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Filter By Player Id", Keywords = "Spacetime Filter Player"), Category = "SpacetimeDbLib")
	static UStdbPlayerComponent* FilterPlayerComponentsById(FString Id, TArray<UStdbPlayerComponent*> Players);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "[Reducer] Update Player Position", Keywords = "Spacetime Update Player Position"), Category = "SpacetimeDbLib")
	static void UpdatePlayerPositionReducer(USpacetimeClientComponent* SpacetimeClient, FVector3f Position, FRotator3f Rotation, FVector3f Velocity, bool Moving);
	
};
