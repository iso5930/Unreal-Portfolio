// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "HT_CharacterSlotWidget.generated.h"

USTRUCT(BlueprintType)
struct FCharacter_Info
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterInfo")
		FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterInfo")
	int Level;
};

/**
 * 
 */
UCLASS()
class HUNTER_API UHT_CharacterSlotWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite)
	FCharacter_Info CharacterInfo;

	UPROPERTY(BlueprintReadWrite)
	FLinearColor BackGroundColor = FLinearColor(1.0f, 1.0f, 1.0f, 1.0f);

public:
	int index;
	bool IsCheck = false;

public:
	void SetSlot(FCharacter_Info Info);
	void SetBackGroundColor(bool Check);

protected:
	virtual void NativeConstruct() override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
};