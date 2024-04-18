// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "components/SpacetimeEntityComponent.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SpacetimeDbLib/Public/Utils.h"
#include "structs/EntityComponent.h"
#include "nlohmann/json.hpp"
#include "EntityTable.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNPROJECT_API UEntityTable : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Deserialize Entity", Keywords = "Spacetime Entity Deserialize"), Category = "SpacetimeDbLib")
	static FEntityComponent DeserializeEntity(FString EntityJson);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Filter By Entity Id", Keywords = "Spacetime Filter Entity"), Category = "SpacetimeDbLib")
	static USpacetimeEntityComponent* FilterEntityComponentsById(int Id, TArray<USpacetimeEntityComponent*> Entities);

};
