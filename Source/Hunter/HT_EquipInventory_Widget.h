// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "HT_DropItem.h"
#include "HT_EquipInventory_Widget.generated.h"

UENUM(BlueprintType)
enum class E_EQUIP_SLOT_TYPE : uint8
{
	EQUIP_SLOT_UPPER UMETA(DisplayName = "EQUIP_SLOT_UPPER"),
	EQUIP_SLOT_LOWER UMETA(DisplayName = "EQUIP_SLOT_LOWER"),
	EQUIP_SLOT_FOOT UMETA(DisplayName = "EQUIP_SLOT_FOOT"),
	EQUIP_SLOT_WEAPON UMETA(DisplayName = "EQUIP_SLOT_WEAPON"),
	EQUIP_SLOT_END UMETA(DisplayName = "EQUIP_SLOT_END")
};

/**
 * 
 */
UCLASS()
class HUNTER_API UHT_EquipInventory_Widget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<class UHT_InventorySlotWidget*> EquipSlotArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UUserWidget> EquipMoveWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D Postion;
	
public:
	TArray<FItem_Info> Equip_Data;
	FVector2D MouseOffSet;

public:
	UFUNCTION(BlueprintCallable)
	void ReflashSlot();

	UFUNCTION(BlueprintCallable)
	void Init_Equip();

	void LocalEquipInventoryLoad();
	void NetworkEquipInventoryLoad(TArray<FItem_Info> LoadEquipData);

protected:
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& InOperation) override;
};