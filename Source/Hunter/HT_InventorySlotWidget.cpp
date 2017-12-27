// Fill out your copyright notice in the Description page of Project Settings.

#include "Hunter.h"
#include "HT_InventorySlotWidget.h"
#include "HT_InventoryDragDropOperation.h"
#include "HT_GameInstance.h"
#include "HT_InventoryWidget.h"
#include "HT_ItemToolTipWidget.h"

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
			//아이템 사용.
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
			FVector2D InventoryPos = GameInstance->UserInventoryWidget->Postion;

			if (InventoryPos.X >= 640)
			{
				InventoryPos.X -= 350;
			}
			else
			{
				InventoryPos.X += 370;
			}

			UE_LOG(LogClass, Warning, TEXT("%f / %f"), InventoryPos.X, InventoryPos.Y);

			GameInstance->ItemToolTipWidget->SetVisibility(ESlateVisibility::Visible);
			GameInstance->ItemToolTipWidget->RemoveFromParent();
			GameInstance->ItemToolTipWidget->AddToViewport();
			GameInstance->ItemToolTipWidget->SetPositionInViewport(InventoryPos, false);

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