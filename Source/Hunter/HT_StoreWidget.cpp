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
			UE_LOG(LogClass, Warning, TEXT("%s"), TEXT("������ �Ǹ�"));

			//1. ������ �Ǹ� ���� ����(�Ǹ� Ȯ�� UI)
			//2. 1�� �̻��� ��� ���� �������� �κ��丮�� ����.

			//���� ��ġ�� ������ -> ok��ư�� ���ƿ��� ����

			UHT_GameInstance* GameInstance = Cast<UHT_GameInstance>(GetWorld()->GetGameInstance());

			UHT_StoreTradeWidget* TradeWidget = CreateWidget<UHT_StoreTradeWidget>(GetWorld(), GameInstance->StoreTradeWidgetClass);

			FVector2D WidgetPos = InGeometry.AbsoluteToLocal(InDragDropEvent.GetScreenSpacePosition());

			TradeWidget->SetPositionInViewport(WidgetPos, false);
			TradeWidget->AddToViewport();
			TradeWidget->OwnerWidget = Cast<UUserWidget>(this); //�����̴�.. �ʿ䰡 �����ѵ�.. ��...
			TradeWidget->IsBuy = false;

			UHT_InventorySlotWidget* DragSlot = Cast<UHT_InventorySlotWidget>(DragDropOP->DragSlot->GetWidgetFromName("DragSlot"));

			Cast<UHT_InventorySlotWidget>(DragDropOP->PrevSlot)->SlotItem = DragSlot->SlotItem;//���󺹱�.

			if (GameInstance != NULL)
			{
				UHT_InventoryWidget* InventoryWidget = Cast<UHT_InventoryWidget>(GameInstance->UserInventoryWidget);
				InventoryWidget->InventoryData[DragDropOP->DragIndex] = Cast<UHT_InventorySlotWidget>(DragDropOP->PrevSlot)->SlotItem;
				InventoryWidget->ReflashSlot();
			}

			TradeWidget->SlotIndex = DragDropOP->DragIndex;
			TradeWidget->ButtonText = TEXT("�Ǹ�");
		}
	}

	return true;
}