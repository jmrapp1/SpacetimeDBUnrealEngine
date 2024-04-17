#pragma once
#include "ValueAdapter.h"

class JsonValueAdapter : public ValueAdapter<TSharedPtr<FJsonValue>>
{
public:
	virtual bool ReadBool(TSharedPtr<FJsonValue> value) override
	{
		return value.Get()->AsBool();
	}

	virtual FString ReadString(TSharedPtr<FJsonValue> value) override
	{
		return value.Get()->AsString();
	}

	virtual int ReadInteger(TSharedPtr<FJsonValue> value) override
	{
		return value.Get()->AsNumber();
	}

	virtual float ReadFloat(TSharedPtr<FJsonValue> value) override
	{
		FString str = ReadString(value);
		return FCString::Atof(*str);
	}

	virtual FTableValue ReadType(TSharedPtr<FJsonValue> value, AlgebraicType type) override
	{
		FTableValue out;
		out.IsSet = true;
		
		switch (type)
		{
		case AlgebraicType::STRING:
			out.String = ReadString(value);
			break;
		case AlgebraicType::BOOLEAN:
			out.Bool = ReadBool(value);
			break;
		case AlgebraicType::INT:
			out.Int = ReadInteger(value);
			break;
		case AlgebraicType::FLOAT:
			out.Float = ReadFloat(value);
			break;
		default:
			out.IsSet = false;
			break;
		}

		return out;
	}

	virtual FTableValue ReadSome(TSharedPtr<FJsonValue> value, AlgebraicType type) override
	{
		throw std::exception("ReadSome intentionally unimplemented for JsonValueAdapter");
	}
};
