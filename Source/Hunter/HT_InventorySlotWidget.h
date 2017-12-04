// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "HT_DropItem.h"
#include "HT_InventorySlotWidget.generated.h"

/**
 * 
 */
UCLASS()
class HUNTER_API UHT_InventorySlotWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UHT_InventorySlotWidget(const FObjectInitializer & ObjectInitializer);
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FItem_Info SlotItem;

public:
	UPROPERTY(BlueprintReadWrite)
	int SlotIndex;

private:
	class ULocalPlayer* PlayerOwner;

public:
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& InOperation) override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	virtual void NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

	virtual FReply NativeOnMouseMove(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;
};