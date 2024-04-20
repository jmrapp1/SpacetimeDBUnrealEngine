// Fill out your copyright notice in the Description page of Project Settings.


#include "components/SpacetimeEntityComponent.h"


// Sets default values for this component's properties
USpacetimeEntityComponent::USpacetimeEntityComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

void USpacetimeEntityComponent::OnEntityComponentInit(int EntityComponentId)
{
	EntityComponent.Id = EntityComponentId;
}

void USpacetimeEntityComponent::OnEntityComponentInsertion(FEntityComponent NewEntity)
{
	if (EntityComponent.Id != NewEntity.Id)
	{
		return;
	}
	
	EntityComponent.Position = NewEntity.Position;
	EntityComponent.Rotation = NewEntity.Rotation;
	EntityComponent.Velocity = NewEntity.Velocity;
	EntityComponent.Moving = NewEntity.Moving;

	OnEntityInsertion.Broadcast();
}

void USpacetimeEntityComponent::OnEntityComponentUpdate(FEntityComponent EntityUpdate)
{
	if (EntityComponent.Id != EntityUpdate.Id)
	{
		return;
	}
	
	EntityComponent.Position = EntityUpdate.Position;
	EntityComponent.Rotation = EntityUpdate.Rotation;
	EntityComponent.Velocity = EntityUpdate.Velocity;
	EntityComponent.Moving = EntityUpdate.Moving;
	
	OnEntityUpdate.Broadcast();
}

