// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "HT_MonsterHpWidget.generated.h"

/**
 * 
 */
UCLASS()
class HUNTER_API UHT_MonsterHpWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	FString Name;

	UPROPERTY(BlueprintReadWrite)
	FString HpString;

	UPROPERTY(BlueprintReadWrite)
	float HpPersent;
	
public:
	UHT_MonsterHpWidget(const FObjectInitializer& ObjectInitializer);
		
public:
	void MonsterTakeDamege(FString MonsterName, float MonsterHp, float MonsterMaxHP);
};