// Fill out your copyright notice in the Description page of Project Settings.

#include "thread/WsThreadProxy.h"


UWsThreadProxy::UWsThreadProxy(WebsocketClient* wsClient)
{
	this->wsClient = wsClient;
}

uint32 UWsThreadProxy::Run()
{
	try {
		wsClient->run();
	} catch (websocketpp::exception const & e) {
		GEngine->AddOnScreenDebugMessage(-1, 25.f, FColor::Red, "Got a wspp error in thread");
		Utils::LogError(e.what());
		FDebug::DumpStackTraceToLog(ELogVerbosity::Type::Error);
	} catch (const std::exception& e) {
		GEngine->AddOnScreenDebugMessage(-1, 25.f, FColor::Red, "Got an error in thread");
		Utils::LogError(e.what());
		FDebug::DumpStackTraceToLog(ELogVerbosity::Type::Error);
	}

	return 0;
}
