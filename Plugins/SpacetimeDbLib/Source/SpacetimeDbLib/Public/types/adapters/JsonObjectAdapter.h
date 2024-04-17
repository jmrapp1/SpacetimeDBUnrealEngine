#pragma once

#include "ValueAdapter.h"
#include "JsonValueAdapter.h"

class JsonObjectAdapter : public ValueAdapter<TSharedPtr<FJsonObject>>
{
	JsonValueAdapter* adapter;
	
public:
	explicit JsonObjectAdapter(JsonValueAdapter* Adapter)
		: adapter(Adapter)
	{
	}

	virtual FTableValue ReadSome(TSharedPtr<FJsonObject> value, AlgebraicType type) override
	{
		// If "Some<x>" has the "1" key set, then the value isnt set so return that
		if (value->HasField("1"))
		{
			FTableValue out;
			out.IsSet = false;
			return out;
		}
		return adapter->ReadType(value->GetField<EJson::None>(FString("0")), type);
	}

	virtual bool ReadBool(TSharedPtr<FJsonObject> value) override
	{
		throw std::exception("ReadBool intentionally unimplemented for JsonValueAdapter");
	}
	
	virtual FString ReadString(TSharedPtr<FJsonObject> value) override
	{
		throw std::exception("ReadString intentionally unimplemented for JsonValueAdapter");
	}
	
	virtual int ReadInteger(TSharedPtr<FJsonObject> value) override
	{
		throw std::exception("ReadInteger intentionally unimplemented for JsonValueAdapter");
	}
	
	virtual float ReadFloat(TSharedPtr<FJsonObject> value) override
	{
		throw std::exception("ReadFloat intentionally unimplemented for JsonValueAdapter");
	}
	
	virtual FTableValue ReadType(TSharedPtr<FJsonObject> value, AlgebraicType type) override
	{
		throw std::exception("ReadType intentionally unimplemented for JsonValueAdapter");
	}
};
