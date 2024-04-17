#pragma once
#include "types/AlgebraicType.h"
#include "types/TableValue.h"

template <typename T>
class ValueAdapter
{
public:
	virtual ~ValueAdapter() = default;
	
	virtual bool ReadBool(T value) = 0;
	virtual FString ReadString(T value) = 0;
	virtual int ReadInteger(T value) = 0;
	virtual float ReadFloat(T value) = 0;
	
	virtual FTableValue ReadType(T value, AlgebraicType type) = 0;
	virtual FTableValue ReadSome(T value, AlgebraicType type) = 0;
};
