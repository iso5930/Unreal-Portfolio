// Fill out your copyright notice in the Description page of Project Settings.

#include "Hunter.h"
#include "HT_DropItemWidget.h"
#include "ScrollBox.h"
#include "HT_DropItem.h"
#include "HT_DropItemSlotWidget.h"
#include "HT_GameInstance.h"
#include "HT_InventoryWidget.h"

void UHT_DropItemWidget::SetDropItem(AHT_DropItem* NewDropItem)
{
	DropItem = NewDropItem;

	DropItemCnt = DropItem->ItemArray.Num();

	ClearItemList();

	ReflashList();
}

void UHT_DropItemWidget::ReflashList()
{
	for (int32 i = 0; i < DropItemCnt; ++i)
	{
		UUserWidget* NewWidget = CreateWidget<UUserWidget>(GetWorld(), DropItemSlotWidget);

		UHT_DropItemSlotWidget* NewDropItemSlotWidget = Cast<UHT_DropItemSlotWidget>(NewWidget);

		if (NewDropItemSlotWidget != NULL)
		{
			NewDropItemSlotWidget->SetDropItemInfo(DropItem->ItemArray[i]);

			UScrollBox* ScrollBox = Cast<UScrollBox>(this->GetWidgetFromName("DropItemList"));

			ScrollBox->AddChild(NewWidget);
		}
	}
}

void UHT_DropItemWidget::ClearItemList()
{
	UWidget* NewWidget = GetWidgetFromName("DropItemList");

	if (NewWidget != NULL)
	{
		UScrollBox* ScrollBox = Cast<UScrollBox>(NewWidget);

		ScrollBox->ClearChildren();
	}
}

void UHT_DropItemWidget::TakeAllDropItem()
{
	UHT_GameInstance* GameInstance = Cast<UHT_GameInstance>(GetWorld()->GetGameInstance());

	if (GameInstance != NULL)
	{
		if(DropItem != NULL)
		{
			for (int i = 0; i < DropItemCnt; ++i)
			{
				GameInstance->UserInventoryWidget->AddItem(DropItem->ItemArray[i]);
			}

			DropItem->Destroy();
			DropItem = NULL;
			DropItemCnt = 0;

			ClearItemList();

			SetVisibility(ESlateVisibility::Collapsed);
		}
	}
}

void UHT_DropItemWidget::TakeSelectDropItem()
{

}

UHT_DropItemWidget::UHT_DropItemWidget(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	
}