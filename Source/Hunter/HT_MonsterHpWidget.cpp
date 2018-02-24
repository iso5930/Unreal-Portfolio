// Fill out your copyright notice in the Description page of Project Settings.

#include "Hunter.h"
#include "HT_MonsterHpWidget.h"

UHT_MonsterHpWidget::UHT_MonsterHpWidget(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{

}

void UHT_MonsterHpWidget::MonsterTakeDamege(FString MonsterName, float MonsterHp, float MonsterMaxHP)
{
	Name = MonsterName;

	HpString = FString::Printf(TEXT("%d%s%d"), (int)MonsterHp, TEXT(" / "), (int)MonsterMaxHP);

	HpPersent = MonsterHp / MonsterMaxHP * 100;

	HpPersent /= 100.0f;

	if (MonsterHp <= 0)
	{
		this->SetVisibility(ESlateVisibility::Collapsed);
	}
}