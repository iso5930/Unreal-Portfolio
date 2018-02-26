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

	float AccTime;

	bool IsBossSpawn;
	bool IsCreate;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BossMonster")
	TSubclassOf<class AHT_BaseMonster> BossMonster;

public:
	AHT_StageGameMode();

public:
	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void Logout(AController* Exiting) override;
	virtual void Tick(float DeltaSeconds) override;

protected:
	virtual void BeginPlay() override;
};