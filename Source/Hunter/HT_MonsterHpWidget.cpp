// Fill out your copyright notice in the Description page of Project Settings.

#include "Hunter.h"
#include "HT_MonsterHpWidget.h"

UHT_MonsterHpWidget::UHT_MonsterHpWidget(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	ColorArray.Add(FLinearColor(1.0f, 0.0f, 0.0f, 1.0f));
	ColorArray.Add(FLinearColor(1.0f, 1.0f, 0.0f, 1.0f));
	ColorArray.Add(FLinearColor(0.0f, 1.0f, 0.0f, 1.0f));
	ColorArray.Add(FLinearColor(1.0f, 0.0f, 1.0f, 1.0f));
	ColorArray.Add(FLinearColor(0.0f, 1.0f, 1.0f, 1.0f));
}

void UHT_MonsterHpWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	if (CurHP > EndHP)
	{
		CurHP -= InDeltaTime * 100.0f;

		if (CurHP <= EndHP)
		{
			CurHP = EndHP;
		}
	}

	int HpCnt = (int)(CurHP / 100);

	SetMonsterHpCnt(HpCnt);

	HpPersent = CurHP - (HpCnt * 100);
	HpPersent /= 100.0f;

	if (HpCnt == 0)
	{
		FrontColor = ColorArray[HpCnt];
		BackColor = FLinearColor(0.0f, 0.0f, 0.0f, 0.0f);
	}
	else
	{
		HpCnt = HpCnt % 5;

		if (HpCnt == 0)
		{
			BackColor = FLinearColor(1.0f, 0.5f, 0.5f, 1.0f);
		}
		else
		{
			BackColor = ColorArray[HpCnt - 1];
		}

		FrontColor = ColorArray[HpCnt];
	}

	if (CurHP <= 0)
	{
		this->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UHT_MonsterHpWidget::SetMonsterName(FString NewMonsterName)
{
	MonsterName = NewMonsterName;
}

void UHT_MonsterHpWidget::SetMonsterHp(float NewMonsterHp)
{
	MonsterHp = NewMonsterHp;
}

void UHT_MonsterHpWidget::SetMonsterImage(UTexture2D* NewMonsterImage)
{
	MonsterImage = NewMonsterImage;
}

void UHT_MonsterHpWidget::SetMonsterHpCnt(int NewMonsterHpCnt)
{
	if (NewMonsterHpCnt == 0)
	{
		MonsterHpCnt = "";
	}
	else
	{
		MonsterHpCnt = "X" + FString::FromInt(NewMonsterHpCnt);
	}
}

float UHT_MonsterHpWidget::GetMonsterHp()
{
	return MonsterHp;
}

FString UHT_MonsterHpWidget::GetMonsterName()
{
	return MonsterName;
}

void UHT_MonsterHpWidget::MonsterTakeDamege(FString MonsterSpawnName, float StartDamage, float EndDamege, FString NewMonsterName, UTexture2D* NewMonsterImage)
{
	if (SpawnName != MonsterSpawnName)
	{
		SpawnName = MonsterSpawnName;
		StartHP = StartDamage;
		CurHP = StartDamage;
	}

	EndHP = EndDamege;

	SetMonsterName(NewMonsterName);
	SetMonsterImage(NewMonsterImage);
}