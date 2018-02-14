// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "HT_DropItem.h"
#include "HT_InventoryWidget.generated.h"

/**
 * 
 */
UCLASS()
class HUNTER_API UHT_InventoryWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<class UHT_InventorySlotWidget*> InventorySlotArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UUserWidget> InventoryMoveWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D Postion;

	TArray<FItem_Info> InventoryData;
	FVector2D MouseOffSet;

public:
	UFUNCTION(BlueprintCallable)
	void ReflashSlot();

	UFUNCTION(BlueprintCallable)
	void Init_Inventory();

	void LocalInventoryLoad();
	void NetworkInventoryLoad(TArray<FItem_Info> InvenData);

public:
	void AddItem(FItem_Info NewItemInfo);
	void SetPos(FVector2D vPos);

public:
	UHT_InventoryWidget(const FObjectInitializer& ObjectInitializer);

public:
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& InOperation) override;
};