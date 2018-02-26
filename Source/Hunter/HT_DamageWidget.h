// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "HT_DamageWidget.generated.h"

/**
*
*/
UCLASS()
class HUNTER_API UHT_DamageWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	int Damage = 9999;
};