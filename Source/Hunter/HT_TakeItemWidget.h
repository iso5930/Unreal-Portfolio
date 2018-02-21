// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "HT_DropItem.h"
#include "HT_TakeItemWidget.generated.h"

/**
 * 
 */
UCLASS()
class HUNTER_API UHT_TakeItemWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	FItem_Info TakeItem;

public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Event")
	void PlayTakeItemAnim();
};