// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "SpacetimeDbLib/Public/Utils.h"
#include <websocketpp/config/asio_no_tls_client.hpp>
#include <websocketpp/client.hpp>

typedef websocketpp::client<websocketpp::config::asio_client> WebsocketClient;

/**
 * 
 */
class SPACETIMEDBLIB_API UWsThreadProxy : public FRunnable
{
	WebsocketClient* wsClient;
	
public:
	UWsThreadProxy(WebsocketClient* wsClient);
	virtual uint32 Run() override;
};
