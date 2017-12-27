// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "HT_CharacterSelectWidget.generated.h"

/**
 * 
 */
UCLASS()
class HUNTER_API UHT_CharacterSelectWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	int CurIndex; //Ȱ��ȭ�� �ε���.

public:
	void ReflashSlot(int Index, bool IsCheck);
	
public:
	UFUNCTION(BlueprintCallable)
	void DeleteCharacter();

	UFUNCTION(BlueprintCallable)
	bool OnClickGameStart();
};