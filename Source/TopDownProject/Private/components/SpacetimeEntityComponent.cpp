// Fill out your copyright notice in the Description page of Project Settings.


#include "components/SpacetimeEntityComponent.h"


// Sets default values for this component's properties
USpacetimeEntityComponent::USpacetimeEntityComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void USpacetimeEntityComponent::BeginPlay()
{
	Super::BeginPlay();	
}


// Called every frame
void USpacetimeEntityComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                              FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
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
	EntityComponent.Moving = EntityUpdate.Moving;
	
	OnEntityUpdate.Broadcast();
}

