// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "HT_DropItem.h"
#include "HT_CharacterSlotWidget.h"
#include "HT_StagePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class HUNTER_API AHT_StagePlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Widget")
	TSubclassOf<class UUserWidget> StageWidget;

private:
	int PlayerNum;

public:
	UFUNCTION(NetMulticast, Reliable)
	void SetPlayerNum(int Num);

	void SetPlayerNum_Implementation(int Num);

public:
	UFUNCTION(Server, Reliable, WithValidation)
	void GetPlayerInventory(const FString& PlayerName);

	virtual void GetPlayerInventory_Implementation(const FString& PlayerName);

	bool GetPlayerInventory_Validate(const FString& PlayerName);

	UFUNCTION(Server, Reliable, WithValidation)
	void SaveInventoryData(const TArray<FItem_Info>& InvenData, const FString& Name);

	virtual void SaveInventoryData_Implementation(const TArray<FItem_Info>& InvenData, const FString& Name);

	bool SaveInventoryData_Validate(const TArray<FItem_Info>& InvenData, const FString& Name);

	UFUNCTION(Server, Reliable, WithValidation)
	void SaveCharacterData(const TArray<FCharacter_Info>& CharacterData, const FString& UserID);

	void SaveCharacterData_Implementation(const TArray<FCharacter_Info>& CharacterData, const FString& UserID);

	bool SaveCharacterData_Validate(const TArray<FCharacter_Info>& CharacterData, const FString& UserID);

public:
	UFUNCTION(Client, Reliable)
	void SetPlayerInventory(const TArray<FItem_Info>& Inventory);

	virtual void SetPlayerInventory_Implementation(const TArray<FItem_Info>& Inventory);

public:
	virtual void BeginPlay() override;
	virtual void UnPossess() override;
};