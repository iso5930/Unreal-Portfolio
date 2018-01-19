// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "HT_BaseWeapon.h"
#include "HT_Weapon_Scythe.generated.h"

/**
 * 
 */
UCLASS()
class HUNTER_API AHT_Weapon_Scythe : public AHT_BaseWeapon
{
	GENERATED_BODY()

public:
	virtual void Attack() override;
};