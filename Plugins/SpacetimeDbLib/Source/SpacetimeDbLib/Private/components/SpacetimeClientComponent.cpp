// Fill out your copyright notice in the Description page of Project Settings.


#include "components/SpacetimeClientComponent.h"


// Sets default values for this component's properties
USpacetimeClientComponent::USpacetimeClientComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void USpacetimeClientComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                              FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void USpacetimeClientComponent::BeginPlay()
{
	Super::BeginPlay();
	try
	{
		if (!initialized)
		{
			wsClient = new WebsocketClient();

			// log everything
			wsClient->set_access_channels(websocketpp::log::alevel::all);
			wsClient->clear_access_channels(websocketpp::log::alevel::all);
			wsClient->clear_error_channels(websocketpp::log::elevel::all);

			// init io 
			wsClient->init_asio();
			wsClient->set_message_handler(bind(&USpacetimeClientComponent::OnMessage, this, _1, _2));
			wsClient->set_open_handler(bind(&USpacetimeClientComponent::OnConnect, this, _1));
			wsClient->set_fail_handler(bind(&USpacetimeClientComponent::OnConnectFailed, this, _1));

			initialized = true;
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 25.f, FColor::Red, "Tried to reinitialize spacetime manager");
		}
	}
	catch (const std::exception& e)
	{
		GEngine->AddOnScreenDebugMessage(-1, 25.f, FColor::Red, "Got an error on spacetime initlaize");
		Utils::LogError(e.what());
		FDebug::DumpStackTraceToLog(ELogVerbosity::Type::Error);
	}
}

void USpacetimeClientComponent::OnComponentCreated()
{
	Super::OnComponentCreated();
}

void USpacetimeClientComponent::Connect(FString endpoint)
{
	try
	{
		char* uri = TCHAR_TO_ANSI(*endpoint);

		// Get connection
		websocketpp::lib::error_code ec;
		auto connection = wsClient->get_connection(uri, ec);
		connection->append_header("Sec-WebSocket-Protocol", "v1.text.spacetimedb");

		// Check error on build connection
		if (ec)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red,
			                                 FString::Printf(
				                                 TEXT("Could not create connection because: %hs"),
				                                 ec.message().c_str()));
			return;
		}

		// Queue connection
		wsClient->connect(connection);

		// start thread
		UWsThreadProxy* proxy = new UWsThreadProxy(wsClient);
		FRunnableThread::Create(proxy, TEXT("SpacetimeDbWsThread"), 0);
	}
	catch (const std::exception& e)
	{
		GEngine->AddOnScreenDebugMessage(-1, 25.f, FColor::Red, "Got an error on connect()");
		Utils::LogError(e.what());
		FDebug::DumpStackTraceToLog(ELogVerbosity::Type::Error);
	}
}

void USpacetimeClientComponent::OnConnect(websocketpp::connection_hdl connectionHdl)
{
	openedWsConnectionHdl = connectionHdl;
	OnConnection.Broadcast();
}

void USpacetimeClientComponent::OnConnectFailed(websocketpp::connection_hdl connectionHdl)
{
	OnConnectionFailed.Broadcast();
}

void USpacetimeClientComponent::OnMessage(websocketpp::connection_hdl, WebsocketClient::message_ptr msg)
{
	Utils::LogInfo("Message received");
	Utils::LogInfo(msg->get_payload());
	const auto payload = nlohmann::json::parse(msg->get_payload());

	if (payload.contains("IdentityToken"))
	{
		HandleIdentityMessage(payload);
	}
	else if (payload.contains("SubscriptionUpdate"))
	{
		HandleSubscriptionUpdateMessage(payload);
	}
	else if (payload.contains("TransactionUpdate"))
	{
		HandleTransactionUpdate(payload);
	}
	else
	{
		// Trigger event
		Utils::LogInfo("Last event was unknown");
	}
}

void USpacetimeClientComponent::HandleIdentityMessage(nlohmann::basic_json<> payload)
{
	const auto identityJson = payload["IdentityToken"];

	ClientIdentity.Identity = Utils::ToFString(identityJson["identity"].get<std::string>());
	ClientIdentity.Token = Utils::ToFString(identityJson["token"].get<std::string>());
	ClientIdentity.Address = Utils::ToFString(identityJson["address"].get<std::string>());

	// Broadcast event on game thread
	FIdentity clientIdentity = ClientIdentity;
	FOnIdentityReceived* delegateEvent = &OnIdentityReceived;
	AsyncTask(ENamedThreads::GameThread, [clientIdentity, delegateEvent]()
	{ 
			delegateEvent->Broadcast(clientIdentity);
	});
}

void USpacetimeClientComponent::HandleSubscriptionUpdateMessage(nlohmann::basic_json<> payload)
{
	// Broadcast event on game thread
	FSubscriptionUpdate update = FSubscriptionUpdate::Build(payload["SubscriptionUpdate"]);
	FOnSubscriptionUpdate* delegateEvent = &OnSubscriptionUpdate;
	AsyncTask(ENamedThreads::GameThread, [update, delegateEvent]()
	{ 
			delegateEvent->Broadcast(update);
	});
}

void USpacetimeClientComponent::HandleTransactionUpdate(nlohmann::basic_json<> payload)
{
	// Broadcast event on game thread
	FTransactionUpdate update = FTransactionUpdate::Build(payload["TransactionUpdate"]);
	FOnTransactionUpdate* delegateEvent = &OnTransactionUpdate;
	AsyncTask(ENamedThreads::GameThread, [update, delegateEvent]()
	{ 
			delegateEvent->Broadcast(update);
	});
}

void USpacetimeClientComponent::SendWsMessage(std::string payload)
{
	Utils::LogInfo(payload);

	websocketpp::lib::error_code ec;
	wsClient->send(openedWsConnectionHdl, payload, websocketpp::frame::opcode::text, ec);
	if (ec)
	{
		GEngine->AddOnScreenDebugMessage(-1, 25.f, FColor::Red, L"Error sending message");
		Utils::LogError(ec.message());
	}
}

void USpacetimeClientComponent::InvokeReducer(std::string reducerName, nlohmann::basic_json<> args)
{
	SendWsMessage(ReducerAction::BuildReducerAction(reducerName, args));
}

void USpacetimeClientComponent::Subscribe(TArray<FString> queries)
{
	SendWsMessage(SubscribeAction::BuildSubscribe(queries));
}

void USpacetimeClientComponent::Disconnect()
{
	try
	{
		auto connectionPtr = wsClient->get_con_from_hdl(openedWsConnectionHdl);

		// Only close if open
		if (connectionPtr->get_state() != 1)
		{
			return;
		}

		Utils::LogInfo("Closing connection to StDB websocket");

		websocketpp::lib::error_code ec;
		wsClient->close(openedWsConnectionHdl, websocketpp::close::status::going_away, "", ec);
		if (ec)
		{
			GEngine->AddOnScreenDebugMessage(-1, 25.f, FColor::Red, L"Error closing connection");
			Utils::LogError(ec.message());
		}

		Utils::LogInfo("Connection to StDB websocket closed successfully.");
	}
	catch (const std::exception& e)
	{
		GEngine->AddOnScreenDebugMessage(-1, 25.f, FColor::Red, "Got an error while disconnecting");
		Utils::LogError(e.what());
		FDebug::DumpStackTraceToLog(ELogVerbosity::Type::Error);
	}
}

void USpacetimeClientComponent::Cleanup()
{
	wsClient->stop();
	Utils::LogInfo("Stopped StDB websocket client successfully.");
}

void USpacetimeClientComponent::BeginDestroy()
{
	Super::BeginDestroy();
	if (initialized)
	{
		GEngine->AddOnScreenDebugMessage(-1, 25.f, FColor::Yellow, L"Shutting down StDB Connection");
		Disconnect();
		Cleanup();
	}
}
