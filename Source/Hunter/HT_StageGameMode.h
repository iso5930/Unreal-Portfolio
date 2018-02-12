// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameModeBase.h"
#include "HT_StageGameMode.generated.h"

/**
 * 
 */
UCLASS()
class HUNTER_API AHT_StageGameMode : public AGameModeBase
{
	GENERATED_BODY()

private:
	TArray<int> PlayerNums;
	int PlayerCnt;

public:
	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void Logout(AController* Exiting) override;

protected:
	virtual void BeginPlay() override;
};