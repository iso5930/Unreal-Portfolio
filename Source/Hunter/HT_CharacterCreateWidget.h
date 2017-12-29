// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "HT_BaseWeapon.h"
#include "HT_CharacterCreateWidget.generated.h"

/**
 * 
 */
UCLASS()
class HUNTER_API UHT_CharacterCreateWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	E_WEAPON_TYPE StartWeaponType;

public:
	UFUNCTION(BlueprintCallable)
	void CreateCharacter(FString Name);
};