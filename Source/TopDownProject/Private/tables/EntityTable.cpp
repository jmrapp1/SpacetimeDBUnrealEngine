// Fill out your copyright notice in the Description page of Project Settings.


#include "tables/EntityTable.h"

FEntityComponent UEntityTable::DeserializeEntity(FString EntityJson)
{
	auto entityJson = Utils::ParseJsonArray(Utils::ToString(EntityJson));
	
	FEntityComponent entity;
	entity.Id = entityJson[0]->AsNumber();

	auto posArray = entityJson[1]->AsArray();
	entity.Position = FVector3f(
		posArray[0]->AsNumber(),
		posArray[1]->AsNumber(),
		posArray[2]->AsNumber()
	);

	auto rotArray = entityJson[2]->AsArray();
	entity.Rotation = FRotator3f(
		rotArray[0]->AsNumber(),
		rotArray[1]->AsNumber(),
		rotArray[2]->AsNumber()
	);

	entity.Moving = entityJson[3]->AsBool();

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
