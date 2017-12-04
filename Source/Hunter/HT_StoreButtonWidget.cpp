// Fill out your copyright notice in the Description page of Project Settings.

#include "Hunter.h"
#include "HT_StoreButtonWidget.h"
#include "HT_BaseNPC.h"
#include "HT_GameInstance.h"
#include "HT_StoreSlotWidget.h"
#include "ScrollBox.h"

void UHT_StoreButtonWidget::Button_Use()
{
	UHT_GameInstance* GameInstance = Cast<UHT_GameInstance>(GetWorld()->GetGameInstance());

	UUserWidget* StoreWidget = CreateWidget<UUserWidget>(GetWorld(), GameInstance->StoreWidgetClass);
	StoreWidget->AddToViewport();

	UScrollBox* ScrollBox = Cast<UScrollBox>(StoreWidget->GetWidgetFromName("ItemScrollBox"));

	for(int i = 0; i < OwnerNPC->StoreItem.Num(); ++i)
	{
		UHT_StoreSlotWidget* SlotWidget = CreateWidget<UHT_StoreSlotWidget>(GetWorld(), GameInstance->StoreSlotWidgetClass);

		SlotWidget->SetItemIndex(OwnerNPC->StoreItem[i]);

		ScrollBox->AddChild(SlotWidget);
	}
}