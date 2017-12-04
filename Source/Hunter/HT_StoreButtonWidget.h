// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "HT_ButtonWidget.h"
#include "HT_StoreButtonWidget.generated.h"

/**
 * 
 */
UCLASS()
class HUNTER_API UHT_StoreButtonWidget : public UHT_ButtonWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	virtual void Button_Use() override;
};