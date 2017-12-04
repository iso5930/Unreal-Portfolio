// Fill out your copyright notice in the Description page of Project Settings.

#include "Hunter.h"
#include "HT_StoreTradeWidget.h"
#include "HT_StoreSlotWidget.h"
#include "HT_DropItem.h"
#include "HT_GameInstance.h"
#include "HT_InventoryWidget.h"

int UHT_StoreTradeWidget::OnBuyButtonClick()
{
	if (IsBuy)
	{
		//상점에서 생성.
		UHT_GameInstance* GameInstance = Cast<UHT_GameInstance>(GetWorld()->GetGameInstance());

		UHT_StoreSlotWidget* SlotWidget = Cast<UHT_StoreSlotWidget>(OwnerWidget);

		FItem_Info BuyItem = GameInstance->Item_DataBase[SlotWidget->GetItemIndex()];

		BuyItem.Item_Cnt = ItemCount;

		GameInstance->UserInventoryWidget->AddItem(BuyItem);
	}
	else
	{
		//인벤토리에서 생성.
		
		//아이템의 정보를
		UHT_GameInstance* GameInstance = Cast<UHT_GameInstance>(GetWorld()->GetGameInstance());

		UHT_InventoryWidget* InventoryWidget = GameInstance->UserInventoryWidget;

		int ItemCnt = InventoryWidget->InventoryData[SlotIndex].Item_Cnt - ItemCount;

		if (ItemCnt == 0)
		{
			InventoryWidget->InventoryData[SlotIndex] = FItem_Info();
			InventoryWidget->ReflashSlot();
		}
		else
		{
			InventoryWidget->InventoryData[SlotIndex].Item_Cnt = ItemCnt;
			InventoryWidget->ReflashSlot();
		}
	}

	RemoveFromParent();

	return ItemCount;
}

void UHT_StoreTradeWidget::OnCancelButtonClick()
{
	RemoveFromParent();
}

void UHT_StoreTradeWidget::OnPlusButtonClick()
{
	ItemCount += 1;

	UHT_GameInstance* GameInstance = Cast<UHT_GameInstance>(GetWorld()->GetGameInstance());

	int ItemMaxCount = 0;

	if (IsBuy)
	{
		UHT_StoreSlotWidget* SlotWidget = Cast<UHT_StoreSlotWidget>(OwnerWidget);

		ItemMaxCount = GameInstance->Item_DataBase[SlotWidget->GetItemIndex()].Item_MaxCnt;
	}
	else
	{
		ItemMaxCount = GameInstance->UserInventoryWidget->InventoryData[SlotIndex].Item_Cnt;
	}

	if (ItemCount >= ItemMaxCount)
	{
		ItemCount = ItemMaxCount;
	}
}

void UHT_StoreTradeWidget::OnMinusButtonClick()
{
	ItemCount -= 1;

	if (ItemCount == 0)
	{
		ItemCount = 1;
	}
}