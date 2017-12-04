// Fill out your copyright notice in the Description page of Project Settings.

#include "Hunter.h"
#include "HT_InventoryWidget.h"
#include "HT_InventorySlotWidget.h"
#include "HT_InventoryDragDropOperation.h"

void UHT_InventoryWidget::ReflashSlot()
{
	for (int i = 0; i < 30; ++i)
	{
		InventorySlotArray[i]->SlotItem = InventoryData[i];
	}
}

void UHT_InventoryWidget::AddItem(FItem_Info NewItemInfo)
{
	if (NewItemInfo.Item_MaxCnt > 1)//중복이 있을수 있다.
	{
		int ItemCnt = NewItemInfo.Item_Cnt;

		bool IsCheck = false;

		for (int i = 0; i < InventoryData.Num(); ++i)
		{
			if (InventoryData[i].Item_Name == NewItemInfo.Item_Name)
			{
				if (InventoryData[i].Item_Cnt != InventoryData[i].Item_MaxCnt) //맥시멈이 아닐때.
				{
					InventoryData[i].Item_Cnt += ItemCnt;

					if (InventoryData[i].Item_Cnt >= InventoryData[i].Item_MaxCnt) //넘기거나 딱 맞을때.
					{
						ItemCnt = InventoryData[i].Item_Cnt - InventoryData[i].Item_MaxCnt;

						InventoryData[i].Item_Cnt = InventoryData[i].Item_MaxCnt;
					}
					else
					{
						ItemCnt = 0;
					}

					if (ItemCnt == 0)
					{
						IsCheck = true;

						break;
					}
				}
			}
		}

		if (IsCheck == false)
		{
			for (int i = 0; i < InventoryData.Num(); ++i)
			{
				if (InventoryData[i].Item_Image == NULL)
				{
					InventoryData[i] = NewItemInfo;

					break;
				}
			}
		}
	}
	else
	{
		for (int i = 0; i < InventoryData.Num(); ++i)
		{
			if (InventoryData[i].Item_Image == NULL)
			{
				InventoryData[i] = NewItemInfo;

				break;
			}
		}
	}

	ReflashSlot();
}

void UHT_InventoryWidget::SetPos(FVector2D vPos)
{
	this->SetPositionInViewport(vPos, false);
}

UHT_InventoryWidget::UHT_InventoryWidget(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	for (int i = 0; i < 30; ++i)
	{
		InventoryData.Add(FItem_Info());
	}
}

FReply UHT_InventoryWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply Reply = FReply::Handled();

	if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
	{
		TSharedPtr<SWidget> DetectingDrag = this->GetCachedWidget();

		MouseOffSet = InMouseEvent.GetScreenSpacePosition();

		MouseOffSet = InGeometry.AbsoluteToLocal(MouseOffSet);

		if (DetectingDrag.IsValid())
		{
			Reply = Reply.DetectDrag(DetectingDrag.ToSharedRef(), EKeys::LeftMouseButton);
		}
	}

	return Reply;
}

void UHT_InventoryWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& InOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, InOperation);

	UHT_InventoryDragDropOperation* DragDropOp = NewObject<UHT_InventoryDragDropOperation>(UHT_InventoryDragDropOperation::StaticClass());

	DragDropOp->Pivot = EDragPivot::MouseDown;

	UUserWidget* pWidget = CreateWidget<UUserWidget>(GetWorld(), InventoryMoveWidget);

	this->SetVisibility(ESlateVisibility::Collapsed);

	if (DragDropOp)
	{
		DragDropOp->Payload = pWidget;
		DragDropOp->DefaultDragVisual = pWidget;
		DragDropOp->DragOffSet = MouseOffSet;
		DragDropOp->DragType = E_ITEM_DROP_TYPE::ITEM_DROP_INVENTORY;

		InOperation = DragDropOp;
	}
}