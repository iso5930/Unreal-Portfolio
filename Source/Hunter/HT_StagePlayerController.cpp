// Fill out your copyright notice in the Description page of Project Settings.

#include "Hunter.h"
#include "HT_StagePlayerController.h"
#include "HT_InventoryWidget.h"
#include "HT_GameInstance.h"
#include "HT_DropItemWidget.h"
#include "HT_StageWidget.h"

void AHT_StagePlayerController::BeginPlay()
{
	Super::BeginPlay();

	/* 클라이언트에서만 UI를 생성 */

	if (GetWorld()->IsClient() == true) 
	{
		UUserWidget* NewWidget = CreateWidget<UUserWidget>(GetWorld(), StageWidget);
		NewWidget->AddToViewport();

		UHT_GameInstance* GameInstance = Cast<UHT_GameInstance>(GetWorld()->GetGameInstance());

		if (GameInstance != NULL)
		{
			GameInstance->UserInventoryWidget = Cast<UHT_InventoryWidget>(NewWidget->GetWidgetFromName("InventoryWidget"));
			GameInstance->UserInventoryWidget->SetVisibility(ESlateVisibility::Collapsed);

			GameInstance->DropItemWidget = Cast<UHT_DropItemWidget>(NewWidget->GetWidgetFromName("DropItemWidget"));
			GameInstance->DropItemWidget->SetVisibility(ESlateVisibility::Collapsed);

			GameInstance->ItemToolTipWidget = Cast<UUserWidget>(NewWidget->GetWidgetFromName("ItemToolTipWidget"));
			GameInstance->ItemToolTipWidget->SetVisibility(ESlateVisibility::Collapsed);

			GameInstance->ChattingInputWidget = Cast<UUserWidget>(NewWidget->GetWidgetFromName("ChattingInputWidget"));
			GameInstance->ChattingInputWidget->SetVisibility(ESlateVisibility::Collapsed);

			GameInstance->ChattingWidget = Cast<UUserWidget>(NewWidget->GetWidgetFromName("ChattingLogWidget"));

			GameInstance->StageWidet = Cast<UHT_StageWidget>(NewWidget);
		}
	}
}