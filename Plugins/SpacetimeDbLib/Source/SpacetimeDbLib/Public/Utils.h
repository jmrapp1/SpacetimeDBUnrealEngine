#pragma once

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

	static TSharedPtr<FJsonValue> ParseJsonValue(std::string const str) {
		TSharedPtr<FJsonValue> jsonParsed;
    	TSharedRef<TJsonReader<>> jsonReader = TJsonReaderFactory<>::Create(str.c_str());
    	if (FJsonSerializer::Deserialize(jsonReader, jsonParsed))
    	{
    		return jsonParsed;
    	}
		return nullptr;
	}

	static TSharedPtr<FJsonObject> ParseJsonObject(std::string const str) {
		TSharedPtr<FJsonValue> json = ParseJsonValue(str);
		if (json != nullptr)
		{
			return json->AsObject();
		}
		return nullptr;
	}

	static TArray<TSharedPtr<FJsonValue>> ParseJsonArray(std::string const str) {
		TSharedPtr<FJsonValue> json = ParseJsonValue(str);
		if (json != nullptr)
		{
			return json->AsArray();
		}
		return TArray<TSharedPtr<FJsonValue>>();
	}
	
	static FString JsonToFString(TSharedPtr<FJsonObject> json)
	{
		FString jsonString;
		TSharedRef<TJsonWriter<>> writer = TJsonWriterFactory<>::Create(&jsonString);
		FJsonSerializer::Serialize<>(json.ToSharedRef(), writer);
		return jsonString;
	}
	
	static FString JsonToFString(TArray<TSharedPtr<FJsonValue>> json)
	{
		FString jsonString;
		TSharedRef<TJsonWriter<>> writer = TJsonWriterFactory<>::Create(&jsonString);
		FJsonSerializer::Serialize<>(json, writer);
		return jsonString;
	}
	
};
