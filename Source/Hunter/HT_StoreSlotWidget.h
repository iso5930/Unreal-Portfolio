// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "HT_StoreSlotWidget.generated.h"

/**
 * 
 */
UCLASS()
class HUNTER_API UHT_StoreSlotWidget : public UUserWidget
{
	GENERATED_BODY()

private:
	int StoreItemIndex;

public:
	UPROPERTY(BlueprintReadWrite)
	FString ItemName;

	UPROPERTY(BlueprintReadWrite)
	UTexture2D* ItemImage;

public:
	void SetItemIndex(int Index);

public:
	int GetItemIndex();
	
public:
	virtual FReply NativeOnMouseButtonDoubleClick(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
};