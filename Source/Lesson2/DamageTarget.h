// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "DamageTarget.generated.h"

USTRUCT(BlueprintType)
struct FMyStruct
{
	GENERATED_BODY();
	
public:
	UPROPERTY()
	APawn* Instigator;
	UPROPERTY()
	APawn* DamageMaker;
	UPROPERTY()
	float Damage = 0.0f;
};
struct FDamageInfo
{
	
};

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UDamageTarget : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class LESSON2_API IDamageTarget
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual void TakeDamage(const FDamageInfo& DamageInfo) = 0;
};
