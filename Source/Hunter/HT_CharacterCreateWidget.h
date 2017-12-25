// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "HT_CharacterCreateWidget.generated.h"

/**
 * 
 */
UCLASS()
class HUNTER_API UHT_CharacterCreateWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void CreateCharacter(FString Name);
};