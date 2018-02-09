// Fill out your copyright notice in the Description page of Project Settings.

#include "Hunter.h"
#include "HT_InventorySlotWidget.h"
#include "HT_InventoryDragDropOperation.h"
#include "HT_GameInstance.h"
#include "HT_InventoryWidget.h"
#include "HT_ItemToolTipWidget.h"
#include "HT_EquipInventory_Widget.h"
#include "HT_BaseCharacter.h"

UHT_InventorySlotWidget::UHT_InventorySlotWidget(const FObjectInitializer & ObjectInitializer)
	:Super(ObjectInitializer)
{
	//
}

FReply UHT_InventorySlotWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply Reply = FReply::Handled();

	if (SlotItem.Item_Image != NULL)
	{
		if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
		{
			TSharedPtr<SWidget> DetectingDrag = this->GetCachedWidget();

			if (DetectingDrag.IsValid())
			{
				Reply = Reply.DetectDrag(DetectingDrag.ToSharedRef(), EKeys::LeftMouseButton);
			}
		}
		else if (InMouseEvent.GetEffectingButton() == EKeys::RightMouseButton)
		{
			UHT_GameInstance* GameInstance = Cast<UHT_GameInstance>(GetWorld()->GetGameInstance());

			if (GameInstance == NULL)
				return Reply;

			UHT_InventoryWidget* InventoryWidget = Cast<UHT_InventoryWidget>(GameInstance->UserInventoryWidget);

			if (InventoryWidget == NULL)
				return Reply;

			APawn* Actor = GetWorld()->GetFirstLocalPlayerFromController()->GetPlayerController(GetWorld())->GetPawn();

			AHT_BaseCharacter* Player = Cast<AHT_BaseCharacter>(Actor);

			if (Player != NULL)
			{
				UE_LOG(LogClass, Warning, TEXT("%s"), TEXT("캐스팅 성공"));
			}
			else if(Player == NULL)
			{
				UE_LOG(LogClass, Warning, TEXT("%s"), TEXT("캐스팅 실패"));
			}

			FItem_Info TempItem = InventoryWidget->InventoryData[SlotIndex];

			if (ItemSlotType == E_ITEM_SLOT_TYPE::ITEM_SLOT_INVENTORY)
			{
				switch (SlotItem.Item_Type)
				{
				case E_ITEM_TYPE::ITEM_TYPE_EQUIP:

					break;

				case E_ITEM_TYPE::ITEM_TYPE_WEAPON_SCYTHE:

					InventoryWidget->InventoryData[SlotIndex] = GameInstance->EquipWidget->Equip_Data[(int)E_EQUIP_SLOT_TYPE::EQUIP_SLOT_WEAPON];
					GameInstance->EquipWidget->Equip_Data[(int)E_EQUIP_SLOT_TYPE::EQUIP_SLOT_WEAPON] = TempItem;

					Player->WeaponChange(TempItem);

					GameInstance->EquipWidget->ReflashSlot();

					break;

				case E_ITEM_TYPE::ITEM_TYPE_WEAPON_DUAL_BLADE:

					InventoryWidget->InventoryData[SlotIndex] = GameInstance->EquipWidget->Equip_Data[(int)E_EQUIP_SLOT_TYPE::EQUIP_SLOT_WEAPON];
					GameInstance->EquipWidget->Equip_Data[(int)E_EQUIP_SLOT_TYPE::EQUIP_SLOT_WEAPON] = TempItem;

					Player->WeaponChange(TempItem);

					GameInstance->EquipWidget->ReflashSlot();

					break;
				}
			}
			else if (ItemSlotType == E_ITEM_SLOT_TYPE::ITEM_SLOT_EQUIP)
			{
				
			}		

			InventoryWidget->ReflashSlot();
		}
	}

	return Reply;
}

void UHT_InventorySlotWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& InOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, InOperation);

	UHT_GameInstance* GameInstance = Cast<UHT_GameInstance>(GetWorld()->GetGameInstance());

	if (GameInstance != NULL)
	{
		UHT_InventoryWidget* InventoryWidget = Cast<UHT_InventoryWidget>(GameInstance->UserInventoryWidget);

		UUserWidget* NewWidget = CreateWidget<UUserWidget>(GetWorld(), GameInstance->InventorySlotDragWidget);

		UHT_InventoryDragDropOperation* DragDropOp = NewObject<UHT_InventoryDragDropOperation>(UHT_InventoryDragDropOperation::StaticClass());

		Cast<UHT_InventorySlotWidget>(NewWidget->GetWidgetFromName("DragSlot"))->SlotItem = SlotItem;

		SlotItem = FItem_Info();

		InventoryWidget->InventoryData[SlotIndex] = SlotItem;

		if (DragDropOp)
		{
			DragDropOp->DragIndex = SlotIndex;
			DragDropOp->DragSlot = NewWidget;
			DragDropOp->PrevSlot = this;

			DragDropOp->Payload = NewWidget;
			DragDropOp->DefaultDragVisual = NewWidget;
			DragDropOp->DragType = E_ITEM_DROP_TYPE::ITEM_DROP_SLOT;
			InOperation = DragDropOp;
		}

		InventoryWidget->ReflashSlot();
	}
}

bool UHT_InventorySlotWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	UHT_InventoryDragDropOperation* DragDropOp = Cast<UHT_InventoryDragDropOperation>(InOperation);

	if (DragDropOp != NULL)
	{
		if (DragDropOp->DragType == E_ITEM_DROP_TYPE::ITEM_DROP_SLOT)
		{
			UHT_InventorySlotWidget* DragSlot = Cast<UHT_InventorySlotWidget>(DragDropOp->DragSlot->GetWidgetFromName("DragSlot"));

			Cast<UHT_InventorySlotWidget>(DragDropOp->PrevSlot)->SlotItem = SlotItem;

			SlotItem = DragSlot->SlotItem;
			DragSlot->SlotItem = FItem_Info();

			UHT_GameInstance* GameInstance = Cast<UHT_GameInstance>(GetWorld()->GetGameInstance());

			if (GameInstance != NULL)
			{
				UHT_InventoryWidget* InventoryWidget = Cast<UHT_InventoryWidget>(GameInstance->UserInventoryWidget);

				InventoryWidget->InventoryData[SlotIndex] = SlotItem;
				InventoryWidget->InventoryData[DragDropOp->DragIndex] = Cast<UHT_InventorySlotWidget>(DragDropOp->PrevSlot)->SlotItem;
				InventoryWidget->ReflashSlot();
			}
		}
	}

	return false;
}

void UHT_InventorySlotWidget::NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	//throw std::logic_error("The method or operation is not implemented.");
}

FReply UHT_InventorySlotWidget::NativeOnMouseMove(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply Reply = FReply::Handled();

	if (SlotItem.Item_Image != NULL)
	{
		UHT_GameInstance* GameInstance = Cast<UHT_GameInstance>(GetWorld()->GetGameInstance());

		if (GameInstance != NULL)
		{
			FVector2D WidgetPos;

			if (ItemSlotType == E_ITEM_SLOT_TYPE::ITEM_SLOT_INVENTORY)
			{
				WidgetPos = GameInstance->UserInventoryWidget->Postion;
			}
			else if (ItemSlotType == E_ITEM_SLOT_TYPE::ITEM_SLOT_EQUIP)
			{
				WidgetPos = GameInstance->EquipWidget->Postion;
			}

			if (WidgetPos.X >= 640)
			{
				WidgetPos.X -= 350;
			}
			else
			{
				WidgetPos.X += 370;
			}

			//UE_LOG(LogClass, Warning, TEXT("%f / %f"), WidgetPos.X, WidgetPos.Y);

			GameInstance->ItemToolTipWidget->SetVisibility(ESlateVisibility::Visible);
			GameInstance->ItemToolTipWidget->RemoveFromParent();
			GameInstance->ItemToolTipWidget->AddToViewport();
			GameInstance->ItemToolTipWidget->SetPositionInViewport(WidgetPos, false);

			UHT_ItemToolTipWidget* ItemToolTipWidget = Cast<UHT_ItemToolTipWidget>(GameInstance->ItemToolTipWidget);
			ItemToolTipWidget->ItemImage = SlotItem.Item_Image;
			ItemToolTipWidget->ItemName = SlotItem.Item_Name;
		}
	}

	//UE_LOG(LogClass, Warning, TEXT("%s %d"), TEXT("Mouse Over Function"), SlotIndex);

	return Reply;
}

void UHT_InventorySlotWidget::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	UHT_GameInstance* GameInstance = Cast<UHT_GameInstance>(GetWorld()->GetGameInstance());

	if (GameInstance != NULL)
	{
		GameInstance->ItemToolTipWidget->SetVisibility(ESlateVisibility::Collapsed);
	}

	UE_LOG(LogClass, Warning, TEXT("%s %d"), TEXT("Mouse Leave Function"), SlotIndex);
}