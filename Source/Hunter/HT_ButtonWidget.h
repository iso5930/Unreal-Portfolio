// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "HT_ButtonWidget.generated.h"

/**
 * 
 */
UCLASS()
class HUNTER_API UHT_ButtonWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UUserWidget* OwnerWidget = NULL;
	class AHT_BaseNPC* OwnerNPC = NULL;

public:
	void SetOwnerWidget(UUserWidget* Owner);
	void SetOwnerNPC(AHT_BaseNPC* Owner);
	
public:
	UFUNCTION(BlueprintCallable)
	virtual void Button_Use();
};