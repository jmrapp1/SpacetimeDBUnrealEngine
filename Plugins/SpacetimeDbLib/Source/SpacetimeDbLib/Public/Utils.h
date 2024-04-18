#pragma once
#include "nlohmann/json.hpp"

class Utils
{
public:
	static std::string ToString(FString str)
	{
		return std::string(TCHAR_TO_UTF8(*str));
	}

	static FString ToFString(char const* str)
	{
		return FString(strlen(str), str);
	}

	static FString ToFString(std::string str)
	{
		return FString(strlen(str.c_str()), str.c_str());
	}
	
	static void LogInfo(char const* str)
	{
		UE_LOG(LogTemp, Log,TEXT("%s"), *ToFString(str));
	}
	
	static void LogInfo(std::string str)
	{
		UE_LOG(LogTemp, Log,TEXT("%s"), *ToFString(str.c_str()));
	}
	
	static void LogInfo(FString str)
	{
		UE_LOG(LogTemp, Log,TEXT("%s"), *str);
	}
	
	static void LogError(char const* str)
	{
		UE_LOG(LogTemp, Error,TEXT("%s"), *ToFString(str));
	}
	
	static void LogError(std::string str)
	{
		UE_LOG(LogTemp, Error,TEXT("%s"), *ToFString(str.c_str()));
	}

};
