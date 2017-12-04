// Fill out your copyright notice in the Description page of Project Settings.

#include "Hunter.h"
#include "HT_DropItemSlotWidget.h"

void UHT_DropItemSlotWidget::SetDropItemInfo(FItem_Info NewDropItemInfo)
{
	DropItemInfo = NewDropItemInfo;

	ItemName = DropItemInfo.Item_Name;
	ItemImage = DropItemInfo.Item_Image;

	ItemCnt = FString::FromInt(DropItemInfo.Item_Cnt);
}

FReply UHT_DropItemSlotWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply Reply = FReply::Handled();

	if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
	{
		if (IsCheck)
		{
			IsCheck = false;

			BackGroundColor = FLinearColor(1.0f, 1.0f, 1.0f, 0.1f);
		}
		else
		{
			BackGroundColor = FLinearColor(1.0f, 0.0f, 0.0f, 0.1f);

			IsCheck = true;
		}
	}

	return Reply;
}