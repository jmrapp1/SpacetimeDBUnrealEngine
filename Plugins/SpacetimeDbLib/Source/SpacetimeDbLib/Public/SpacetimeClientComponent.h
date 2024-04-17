// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include <websocketpp/config/asio_no_tls_client.hpp>
#include <websocketpp/client.hpp>
#include "Utils.h"
#include "thread/WsThreadProxy.h"
#include "events/MessageReceivedEvent.h"
#include "types/messages/SubscriptionUpdate.h"
#include "types/messages/TableUpdate.h"
#include "types/Identity.h"
#include "types/messages/TransactionUpdate.h"
#include "actions/SubscribeAction.h"
#include "nlohmann/json.hpp"
#include "SpacetimeClientComponent.generated.h"

using websocketpp::lib::bind;
using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;

typedef websocketpp::client<websocketpp::config::asio_client> WebsocketClient;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(
  FOnMessageReceived,
  FString, Payload 
);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(
  FOnSubscriptionUpdate,
  FSubscriptionUpdate, Update
);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(
  FOnTransactionUpdate,
  FTransactionUpdate, Update
);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(
  FOnConnection
);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(
  FOnConnectionFailed
);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(
  FOnIdentityReceived,
  FIdentity, Identity
);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SPACETIMEDBLIB_API USpacetimeClientComponent : public UActorComponent
{
	GENERATED_BODY()
	
	bool initialized = false;
	WebsocketClient* wsClient = nullptr;
	websocketpp::connection_hdl openedWsConnectionHdl;

protected:
	virtual void BeginPlay() override;
	
public:
	USpacetimeClientComponent();

	UPROPERTY(BlueprintReadWrite)
	FIdentity ClientIdentity;

	virtual void BeginDestroy() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
							   FActorComponentTickFunction* ThisTickFunction) override;
	// Websocket handlers
	void OnConnect(websocketpp::connection_hdl connectionHdl);
	void OnConnectFailed(websocketpp::connection_hdl connectionHdl);
	void OnMessage(websocketpp::connection_hdl, WebsocketClient::message_ptr msg);
	void SendWsMessage(std::string payload);

	// Calls
	void InvokeReducer(FString reducerName, TArray<TSharedPtr<FJsonValue>> args);
	void InvokeReducer(std::string reducerName, nlohmann::basic_json<> args);

	// Message handlers
	void HandleIdentityMessage(TSharedPtr<FJsonObject> payload);
	void HandleSubscriptionUpdateMessage(TSharedPtr<FJsonObject> payload);
	void HandleTransactionUpdate(TSharedPtr<FJsonObject> payload);
	
	// Public functions
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Create connection with Spacetime DB", Keywords = "Spacetime connect"), Category = "SpacetimeDbLib")
	void Connect(FString endpoint);
	
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Disconnect from Spacetime DB", Keywords = "Spacetime disconnect"), Category = "SpacetimeDbLib")
	void Disconnect();
	
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Cleanup Spacetime DB resources", Keywords = "Spacetime cleanup clean"), Category = "SpacetimeDbLib")
	void Cleanup();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Subscribe to queries", Keywords = "Spacetime subscribe"), Category = "SpacetimeDbLib")
	void Subscribe(TArray<FString> queries);

	// Events
	// https://medium.com/@rdolivo/unreal-engine-how-to-declare-a-custom-event-in-c-313cc5dd975a
	UPROPERTY(BlueprintAssignable)
	FOnMessageReceived OnMessageReceived;
	
	UPROPERTY(BlueprintAssignable)
	FOnConnection OnConnection;
	
	UPROPERTY(BlueprintAssignable)
	FOnConnectionFailed OnConnectionFailed;
	
	UPROPERTY(BlueprintAssignable)
	FOnIdentityReceived OnIdentityReceived;
	
	UPROPERTY(BlueprintAssignable)
	FOnSubscriptionUpdate OnSubscriptionUpdate;
	
	UPROPERTY(BlueprintAssignable)
	FOnTransactionUpdate OnTransactionUpdate;
};