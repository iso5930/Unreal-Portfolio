// Fill out your copyright notice in the Description page of Project Settings.

#include "Hunter.h"
#include "HT_ChattingLogWidget.h"
#include "HT_GameInstance.h"
#include "ScrollBox.h"
#include "HT_ChattingTextWidget.h"
#include "Runtime/Sockets/Public/Sockets.h"

void UHT_ChattingLogWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	UHT_GameInstance* GameInstance = Cast<UHT_GameInstance>(GetWorld()->GetGameInstance());

	if (GameInstance->IsNetwork && GameInstance->ChattingSocket != NULL)
	{
		uint32 Size = 0;

		if (GameInstance->ChattingSocket->HasPendingData(Size))
		{
			TCHAR szMsg[50] = TEXT("");

			int32 ReadSize = 0;

			GameInstance->ChattingSocket->Recv((uint8*)szMsg, sizeof(TCHAR) * 50, ReadSize);

			UScrollBox* ScrollBox = Cast<UScrollBox>(this->GetWidgetFromName("ChattingLogWidget"));

			UHT_ChattingTextWidget* TextWidget = CreateWidget<UHT_ChattingTextWidget>(GetWorld(), GameInstance->ChattingTextWidgetClass);
						
			ScrollBox->AddChild(TextWidget);
			ScrollBox->ScrollToEnd();

			TextWidget->Init_ChattingText(szMsg);
		}
	}
}