// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "HT_BaseWeapon.h"
#include "HT_LobbyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class HUNTER_API AHT_LobbyPlayerController : public APlayerController
{
	GENERATED_BODY()

private:
	bool IsSuccess = false;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "WidgetClass")
	TSubclassOf<class UUserWidget> CharacterSelectWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "WidgetClass")
	TSubclassOf<class UUserWidget> CharacterSlotWidgetClass;

public:
	UFUNCTION(Server, Reliable, WithValidation)
	void FindUserCharacter(const FString& UserID); //서버에서 계정을 토대로 

	virtual void FindUserCharacter_Implementation(const FString& UserID);

	bool FindUserCharacter_Validate(const FString& UserID);

	UFUNCTION(Client, Reliable)
	void CharacterInfoRecv(const TArray<FCharacter_Info>& Characters);

	virtual void CharacterInfoRecv_Implementation(const TArray<FCharacter_Info>& Characters);

	UFUNCTION(Server, Reliable, WithValidation)
	void CharacterNameCheck(const FString& Name, E_WEAPON_TYPE StartWeaponType);

	virtual void CharacterNameCheck_Implementation(const FString& Name, E_WEAPON_TYPE StartWeaponType);

	bool CharacterNameCheck_Validate(const FString& Name, E_WEAPON_TYPE StartWeaponType);

	UFUNCTION(Client, Reliable)
	void CharacterNameCheckRecv(bool IsCheck, const FString& Name);

	void CharacterNameCheckRecv_Implementation(bool IsCheck, const FString& Name);

protected:
	virtual void BeginPlay() override;
};