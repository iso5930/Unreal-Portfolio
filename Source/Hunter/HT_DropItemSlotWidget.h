// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "HT_DropItem.h"
#include "HT_DropItemSlotWidget.generated.h"

/**
 * 
 */
UCLASS()
class HUNTER_API UHT_DropItemSlotWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	FLinearColor BackGroundColor = FLinearColor(1.0f, 1.0f, 1.0f, 0.1f);

	UPROPERTY(BlueprintReadWrite)
	FString ItemName;

	UPROPERTY(BlueprintReadWrite)
	UTexture2D* ItemImage;

	UPROPERTY(BlueprintReadWrite)
	FString ItemCnt;

public:
	bool IsCheck = false;

public:
	FItem_Info DropItemInfo;

public:
	void SetDropItemInfo(FItem_Info NewDropItemInfo);

public:
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
};