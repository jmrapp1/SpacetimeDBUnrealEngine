// Fill out your copyright notice in the Description page of Project Settings.


#include "tables/EntityTable.h"


FEntityComponent UEntityTable::DeserializeEntity(FString EntityJson)
{
	auto entityJson = nlohmann::json::parse(Utils::ToString(EntityJson));
	
	FEntityComponent entity;
	entity.Id = entityJson[0].get<int>();

	auto posArray = entityJson[1];
	entity.Position = FVector3f(
		posArray[0].get<int>(),
		posArray[1].get<int>(),
		posArray[2].get<int>()
	);

	auto rotArray = entityJson[2];
	entity.Rotation = FRotator3f(
		rotArray[0].get<int>(),
		rotArray[1].get<int>(),
		rotArray[2].get<int>()
		);

	auto velArray = entityJson[3];
	entity.Velocity = FVector3f(
		velArray[0].get<int>(),
		velArray[1].get<int>(),
		velArray[2].get<int>()
	);

	entity.Moving = entityJson[4].get<bool>();

	return entity;
}

USpacetimeEntityComponent* UEntityTable::FilterEntityComponentsById(int Id, TArray<USpacetimeEntityComponent*> Entities)
{
	for (USpacetimeEntityComponent* entity : Entities)
	{
		if (entity->EntityComponent.Id == Id)
		{
			return entity;
		}
	}
	return nullptr;
}
