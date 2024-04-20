// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "structs/EntityComponent.h"
#include "SpacetimeEntityComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(
  FOnEntityComponentInsertion
);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(
  FOnEntityComponentUpdate
);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TOPDOWNPROJECT_API USpacetimeEntityComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	FEntityComponent EntityComponent;
	
	// Sets default values for this component's properties
	USpacetimeEntityComponent();

public:

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "On Entity Component Initialization", Keywords = "Spacetime Entity Component Initialization"), Category = "SpacetimeDbLib")
	void OnEntityComponentInit(int EntityComponentId);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "On Entity Component Insertion", Keywords = "Spacetime Entity Component Insertion"), Category = "SpacetimeDbLib")
	void OnEntityComponentInsertion(FEntityComponent NewEntity);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "On Entity Component Update", Keywords = "Spacetime Entity Component Update"), Category = "SpacetimeDbLib")
	void OnEntityComponentUpdate(FEntityComponent EntityUpdate);
	
	UPROPERTY(BlueprintAssignable)
	FOnEntityComponentInsertion OnEntityInsertion;
	
	UPROPERTY(BlueprintAssignable)
	FOnEntityComponentUpdate OnEntityUpdate;
};
