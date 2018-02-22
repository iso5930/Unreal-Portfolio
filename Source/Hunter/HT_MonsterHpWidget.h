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
	FString MonsterName;

	UPROPERTY(BlueprintReadWrite)
	FString MonsterHpCnt;

	UPROPERTY(BlueprintReadWrite)
	float MonsterHp;

	UPROPERTY(BlueprintReadWrite)
	UTexture2D* MonsterImage;

	UPROPERTY(BlueprintReadWrite)
	FLinearColor FrontColor = FLinearColor(1.0f, 0.0f, 0.0f, 1.0f);

	UPROPERTY(BlueprintReadWrite)
	FLinearColor BackColor = FLinearColor(0.0f, 1.0f, 0.0f, 1.0f);

	UPROPERTY(BlueprintReadWrite)
	float HpPersent;

public:
	TArray<FLinearColor> ColorArray;

	FString SpawnName;

	float StartHP;
	float EndHP;
	float CurHP;

public:
	UHT_MonsterHpWidget(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:
	void SetMonsterName(FString NewMonsterName);
	void SetMonsterHp(float NewMonsterHp);
	void SetMonsterImage(UTexture2D* NewMonsterImage);
	void SetMonsterHpCnt(int NewMonsterHpCnt);

	float GetMonsterHp();
	FString GetMonsterName();

public:
	void MonsterTakeDamege(FString MonsterSpawnName, float StartDamage, float EndDamege, FString NewMonsterName, UTexture2D* NewMonsterImage);
};