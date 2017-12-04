// Fill out your copyright notice in the Description page of Project Settings.

#include "Hunter.h"
#include "HT_LoginWidget.h"
#include "HT_GameInstance.h"
#include "EditableTextBox.h"
#include "HT_LoginThread.h"
#include "HT_MessageBoxWidget.h"
#include "Runtime/Sockets/Public/Sockets.h"

void UHT_LoginWidget::OnLoginButton()
{
	UEditableTextBox* ID_Input = Cast<UEditableTextBox>(this->GetWidgetFromName("ID_Input"));
	UEditableTextBox* PW_Input = Cast<UEditableTextBox>(this->GetWidgetFromName("PW_Input"));

	FString ID = ID_Input->GetText().ToString();
	FString PW = PW_Input->GetText().ToString();

	UHT_GameInstance* GameInstance = Cast<UHT_GameInstance>(GetWorld()->GetGameInstance());

	if (ID.Len() > 0 && PW.Len() > 0)
	{
		GameInstance->Init_Network(ID, PW);

		IsLoginChaking = true;
	}
	else if (ID.Len() == 0)
	{
		UHT_MessageBoxWidget* NewWidget = CreateWidget<UHT_MessageBoxWidget>(GetWorld(), GameInstance->MessageBoxWidgetClass);
		NewWidget->SetMessageText(TEXT("ID를 입력하세요."));
		NewWidget->AddToViewport();
	}
	else if (PW.Len() == 0)
	{
		UHT_MessageBoxWidget* NewWidget = CreateWidget<UHT_MessageBoxWidget>(GetWorld(), GameInstance->MessageBoxWidgetClass);
		NewWidget->SetMessageText(TEXT("PW를 입력하세요."));
		NewWidget->AddToViewport();
	}
}

void UHT_LoginWidget::OnCencelButton()
{
	//FHT_LoginThread::JoyInit()->Shutdown();
}

void UHT_LoginWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	if (IsLoginChaking)
	{
		if (FHT_LoginThread::GetInstance()->IsComplete)
		{
			UHT_GameInstance* GameInstance = Cast<UHT_GameInstance>(GetWorld()->GetGameInstance());

			UHT_MessageBoxWidget* NewWidget = CreateWidget<UHT_MessageBoxWidget>(GetWorld(), GameInstance->MessageBoxWidgetClass);

			if (FHT_LoginThread::GetInstance()->IsSuccess)
			{
				NewWidget->SetMessageText(TEXT("인증 성공!"));

				NewWidget->IsLogin = true;
			}
			else
			{
				NewWidget->SetMessageText(TEXT("인증 실패!"));
				//인증 실패
				NewWidget->IsLogin = false;

				GameInstance->ChattingSocket->Close();
				GameInstance->ChattingSocket = NULL;
			}

			NewWidget->AddToViewport();

			FHT_LoginThread::GetInstance()->Shutdown();
		}
	}
}