// Fill out your copyright notice in the Description page of Project Settings.


#include "components/SpacetimeClientConsumerComponent.h"


USpacetimeClientConsumerComponent::USpacetimeClientConsumerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

USpacetimeClientComponent* USpacetimeClientConsumerComponent::GetSpacetimeClientRef()
{
	if (SpacetimeClient != nullptr)
	{
		return SpacetimeClient;
	}
	
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), SpacetimeClientActorType, FoundActors);
	if (FoundActors.Num() == 0)
	{
		Utils::LogError("Could not find SpacetimeClientActorType inside SpacetimeClientConsumerComponent");
		return nullptr;
	}
	if (FoundActors.Num() > 1)
	{
		Utils::LogError("Found too many instances of SpacetimeClientActorType inside SpacetimeClientConsumerComponent");
		return nullptr;
	}

	SpacetimeClient = FoundActors[0]->FindComponentByClass<USpacetimeClientComponent>();
	if (SpacetimeClient == nullptr)
	{
		Utils::LogError("Found actor but did not find SpacetimeClientComponent - from SpacetimeClientConsumerComponent");
		return nullptr;
	}

	return SpacetimeClient;
}


// Called when the game starts
void USpacetimeClientConsumerComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

