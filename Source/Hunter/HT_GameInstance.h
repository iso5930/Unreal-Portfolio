// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/GameInstance.h"
#include "HT_DropItem.h"
#include "HT_CharacterSlotWidget.h"
#include "HT_GameInstance.generated.h"

/**
 * 
 */

struct MemberInfo
{
	TCHAR ID[20];
	TCHAR PW[20];
};

UCLASS()
class HUNTER_API UHT_GameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	bool IsNetwork = false;

	bool IsNewUser = false;

public:
	class UHT_InventoryWidget* UserInventoryWidget;
	class UUserWidget* ChattingWidget;
	class UUserWidget* ChattingInputWidget;

	class UHT_DropItemWidget* DropItemWidget;
	class UUserWidget* ItemToolTipWidget;

	UPROPERTY(BlueprintReadWrite)
	class UHT_StageWidget* StageWidet;

	class UUserWidget* NPCMenuWidget = NULL;

	class UUserWidget* CharacterSelectWidget = NULL;

	class UHT_EquipInventory_Widget* EquipWidget;

	class UHT_MonsterHpWidget* MonsterHpWidget;

	class UHT_PlayerStateWidget* PlayerStateWidget;

	class UHT_TakeItemWidget* TakeItemWidget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "InventoryWidget")
	TSubclassOf<class UUserWidget> InventorySlotDragWidget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "NPCMenuWidget")
	TSubclassOf<class UUserWidget> NPCMenuWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "StoreWidget")
	TSubclassOf<class UUserWidget> StoreWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "StoreWidget")
	TSubclassOf<class UUserWidget> StoreSlotWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "StoreWidget")
	TSubclassOf<class UUserWidget> StoreTradeWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MessageBoxWidget")
	TSubclassOf<class UUserWidget> MessageBoxWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ChattingWidget")
	TSubclassOf<class UUserWidget> ChattingTextWidgetClass;

public:
	class FSocket* ChattingSocket;

public:
	MemberInfo UserInfo;

	int PlayerNum;

public:
	UPROPERTY(BlueprintReadWrite)
	TArray<FCharacter_Info> CharacterData;

	UPROPERTY(BlueprintReadWrite)
	int CharacterCurIndex;

	TArray<class USkeletalMesh*> WeaponMeshs;
	TArray<class USkeletalMesh*> EquipMeshs;
	TArray<class UTexture2D*> MonsterImages;
	
public:
	UHT_GameInstance();

public:
	UPROPERTY(EditDefaultsOnly, Category = "Item")
	TArray<FItem_Info> Item_DataBase;

public:
	UFUNCTION(BlueprintCallable, Category = "GameInstanceFunction")
	void SetNetwork(bool IsCheck);

	UFUNCTION(BlueprintCallable, Category = "GameInstanceFunction")
	bool GetNetwork();

public:
	void Init_Network(FString ID, FString PW);

private:
	virtual void FinishDestroy() override;
};