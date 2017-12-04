// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "HT_ButtonWidget.h"
#include "HT_QuestButtonWidget.generated.h"

/**
 * 
 */
UCLASS()
class HUNTER_API UHT_QuestButtonWidget : public UHT_ButtonWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	virtual void Button_Use() override;
};