// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SpacetimeClientComponent.h"
#include "Components/ActorComponent.h"
#include "Kismet/GameplayStatics.h"
#include "SpacetimeClientConsumerComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SPACETIMEDBLIB_API USpacetimeClientConsumerComponent : public UActorComponent
{
	GENERATED_BODY()
	
private:
	USpacetimeClientComponent* spacetimeClient;

public:

	UPROPERTY(BlueprintReadWrite)
	TSubclassOf<AActor> SpacetimeClientActorType;
	
	// Sets default values for this component's properties
	USpacetimeClientConsumerComponent();
	
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Get Spacetime Client Reference", Keywords = "Get Spacetime Client Reference"), Category = "SpacetimeDbLib")
	USpacetimeClientComponent* GetSpacetimeClientRef();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

};
