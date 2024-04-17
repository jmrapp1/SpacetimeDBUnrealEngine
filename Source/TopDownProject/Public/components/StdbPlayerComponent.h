// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "structs/FPlayerStruct.h"
#include "StdbPlayerComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TOPDOWNPROJECT_API UStdbPlayerComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite)
	FPlayerStruct Player;
	
	// Sets default values for this component's properties
	UStdbPlayerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "On Player Insertion", Keywords = "Spacetime Player Insertion"), Category = "SpacetimeDbLib")
	void OnPlayerInsertion(FPlayerStruct NewPlayer);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "On Player Update", Keywords = "Spacetime Player Update"), Category = "SpacetimeDbLib")
	void OnPlayerUpdate(FPlayerStruct PlayerUpdate);
};
