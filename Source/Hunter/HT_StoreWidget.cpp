// Fill out your copyright notice in the Description page of Project Settings.

#include "Hunter.h"
#include "HT_StoreWidget.h"
#include "HT_InventoryDragDropOperation.h"
#include "HT_GameInstance.h"
#include "HT_StoreTradeWidget.h"
#include "HT_InventorySlotWidget.h"
#include "HT_InventoryWidget.h"

bool UHT_StoreWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	UHT_InventoryDragDropOperation* DragDropOP = Cast<UHT_InventoryDragDropOperation>(InOperation);

	if (DragDropOP != NULL)
	{
		if (DragDropOP->DragType == E_ITEM_DROP_TYPE::ITEM_DROP_SLOT)
		{
			UE_LOG(LogClass, Warning, TEXT("%s"), TEXT("아이템 판매"));

			//1. 아이템 판매 위젯 띄우기(판매 확인 UI)
			//2. 1개 이상일 경우 남은 아이템은 인벤토리로 복귀.

			//원래 위치로 돌리고 -> ok버튼이 돌아오면 삭제

			UHT_GameInstance* GameInstance = Cast<UHT_GameInstance>(GetWorld()->GetGameInstance());

			UHT_StoreTradeWidget* TradeWidget = CreateWidget<UHT_StoreTradeWidget>(GetWorld(), GameInstance->StoreTradeWidgetClass);

			FVector2D WidgetPos = InGeometry.AbsoluteToLocal(InDragDropEvent.GetScreenSpacePosition());

			TradeWidget->SetPositionInViewport(WidgetPos, false);
			TradeWidget->AddToViewport();
			TradeWidget->OwnerWidget = Cast<UUserWidget>(this); //상점이니.. 필요가 없긴한데.. 흠...
			TradeWidget->IsBuy = false;

			UHT_InventorySlotWidget* DragSlot = Cast<UHT_InventorySlotWidget>(DragDropOP->DragSlot->GetWidgetFromName("DragSlot"));

			Cast<UHT_InventorySlotWidget>(DragDropOP->PrevSlot)->SlotItem = DragSlot->SlotItem;//원상복구.

			if (GameInstance != NULL)
			{
				UHT_InventoryWidget* InventoryWidget = Cast<UHT_InventoryWidget>(GameInstance->UserInventoryWidget);
				InventoryWidget->InventoryData[DragDropOP->DragIndex] = Cast<UHT_InventorySlotWidget>(DragDropOP->PrevSlot)->SlotItem;
				InventoryWidget->ReflashSlot();
			}

			TradeWidget->SlotIndex = DragDropOP->DragIndex;
			TradeWidget->ButtonText = TEXT("판매");
		}
	}

	return true;
}