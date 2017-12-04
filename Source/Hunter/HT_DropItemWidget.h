// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "HT_DropItemWidget.generated.h"

/**
 * 
 */
UCLASS()
class HUNTER_API UHT_DropItemWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UUserWidget> DropItemSlotWidget;
	
private:
	class AHT_DropItem* DropItem;

	int32 DropItemCnt;

public:
	void SetDropItem(AHT_DropItem* NewDropItem);

public:
	UFUNCTION(BlueprintCallable)
	void ReflashList();

	UFUNCTION(BlueprintCallable)
	void ClearItemList();

	UFUNCTION(BlueprintCallable)
	void TakeAllDropItem();

	UFUNCTION(BlueprintCallable)
	void TakeSelectDropItem();

public:
	UHT_DropItemWidget(const FObjectInitializer& ObjectInitializer);
};