// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

struct FJsonNestedArray : FJsonValue
{
	TArray<TSharedPtr<FJsonValue>> elements;

protected:
	virtual FString GetType() const override
	{
		return "Array";
	}

public:
	FJsonNestedArray()
	{
		Type = EJson::Array;
		
	}

	
	
};

