// Fill out your copyright notice in the Description page of Project Settings.

#include "Hunter.h"
#include "HT_ChattingInputWidget.h"
#include "HT_GameInstance.h"
#include "ScrollBox.h"
#include "HT_ChattingTextWidget.h"
#include "Runtime/Sockets/Public/Sockets.h"

bool UHT_ChattingInputWidget::OnTextChange(FString NewText)
{
	int Size = NewText.Len();

	if (Size >= 30)
	{
		return false;
	}
	else
	{
		ChattingText = NewText;
	}

	return true;
}

FString UHT_ChattingInputWidget::OnCommitted(FString InputText)
{
	if (this->GetVisibility() == ESlateVisibility::Visible)
	{
		this->SetVisibility(ESlateVisibility::Collapsed);

		FInputModeGameOnly InputMode;

		APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

		if (PlayerController != NULL)
		{
			PlayerController->SetInputMode(InputMode);
		}

		if (ChattingText.Len() == 0)
		{
			return ChattingText;
		}
		
		UHT_GameInstance* GameInstance = Cast<UHT_GameInstance>(GetWorld()->GetGameInstance());

		if (GameInstance->IsNetwork && GetWorld()->IsClient() == true)
		{	
			//채팅 서버 연결 됬을때.
			ChattingText = GameInstance->UserInfo.ID + FString(TEXT(" : ")) + ChattingText;

			int32 Send = 0;

			GameInstance->ChattingSocket->Send((uint8*)*ChattingText, sizeof(TCHAR) * 50, Send);

			ChattingText = "";
		}
		else
		{
			ChattingText = GameInstance->UserInfo.ID + FString(TEXT(" : ")) + ChattingText;

			UScrollBox* ScrollBox = Cast<UScrollBox>(GameInstance->ChattingWidget->GetWidgetFromName("ChattingLogWidget"));

			UUserWidget* NewWidget = CreateWidget<UUserWidget>(GetWorld(), ChattingTextWidget);

			UHT_ChattingTextWidget* TextWidget = Cast<UHT_ChattingTextWidget>(NewWidget);

			ScrollBox->AddChild(TextWidget);
			ScrollBox->ScrollToEnd();

			TextWidget->Init_ChattingText(ChattingText);

			ChattingText = "";
		}
	}
	
	return ChattingText;
}

void UHT_ChattingInputWidget::NativeConstruct()
{
	InputWidget = (UUserWidget*)GetWidgetFromName("ChattingInputBox");
}