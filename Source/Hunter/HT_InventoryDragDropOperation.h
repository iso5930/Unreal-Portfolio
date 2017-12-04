// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/DragDropOperation.h"
#include "HT_InventoryDragDropOperation.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class E_ITEM_DROP_TYPE : uint8
{
	ITEM_DROP_SLOT UMETA(DisplayName = "ITEM_DROP_SLOT"),
	ITEM_DROP_INVENTORY UMETA(DisplayName = "ITEM_DROP_INVENTORY"),
	ITEM_DROP_EQUIP UMETA(DisplayName = "ITEM_DROP_EQUIP")
};

UCLASS()
class HUNTER_API UHT_InventoryDragDropOperation : public UDragDropOperation
{
	GENERATED_BODY()
	
public:
	class UUserWidget* DragSlot;
	class UUserWidget* PrevSlot;
	int DragIndex;
	FVector2D DragOffSet;
	E_ITEM_DROP_TYPE DragType;
};