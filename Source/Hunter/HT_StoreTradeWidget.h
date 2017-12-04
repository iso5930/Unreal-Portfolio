// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "HT_StoreTradeWidget.generated.h"

/**
 * 
 */
UCLASS()
class HUNTER_API UHT_StoreTradeWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	class UUserWidget* OwnerWidget = NULL;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "StoreTradeWidget")
	int ItemCount = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "StoreTradeWidget")
	FString ButtonText;

	bool IsBuy = false;

	int SlotIndex = 0;

public:
	UFUNCTION(BlueprintCallable, Category = "StoreTradeWidgetFunction")
	int OnBuyButtonClick();

	UFUNCTION(BlueprintCallable, Category = "StoreTradeWidgetFunction")
	void OnCancelButtonClick();

	UFUNCTION(BlueprintCallable, Category = "StoreTradeWidgetFunction")
	void OnPlusButtonClick();

	UFUNCTION(BlueprintCallable, Category = "StoreTradeWidgetFunction")
	void OnMinusButtonClick();
};