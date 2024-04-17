// Fill out your copyright notice in the Description page of Project Settings.


#include "components/StdbPlayerComponent.h"


// Sets default values for this component's properties
UStdbPlayerComponent::UStdbPlayerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UStdbPlayerComponent::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UStdbPlayerComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                         FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UStdbPlayerComponent::OnPlayerInsertion(FPlayerStruct NewPlayer)
{
	Player.Identity = NewPlayer.Identity;
	Player.Name = NewPlayer.Name;
	Player.Online = NewPlayer.Online;
	Player.EntityComponentId = NewPlayer.EntityComponentId;
}

void UStdbPlayerComponent::OnPlayerUpdate(FPlayerStruct PlayerUpdate)
{
	if (PlayerUpdate.Identity != Player.Identity)
	{
		return;
	}

	Player.Name = PlayerUpdate.Name;
	Player.Online = PlayerUpdate.Online;
	Player.EntityComponentId = PlayerUpdate.EntityComponentId;
}

