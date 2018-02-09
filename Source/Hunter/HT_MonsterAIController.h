// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "HT_BaseMonster.h"
#include "HT_MonsterAIController.generated.h"

/**
 * 
 */

class UBlackboardComponent;
class UBehaviorTreeComponent;

UCLASS()
class HUNTER_API AHT_MonsterAIController : public AAIController
{
	GENERATED_BODY()

private:
	UPROPERTY(transient)
	UBlackboardComponent* BlackboardComponent;

	UPROPERTY(transient)
	UBehaviorTreeComponent* BehaviorComponent;

private:
	int EnemyKeyID;

public:
	void SetTarget(APawn* InTarget);

public:
	UFUNCTION(BlueprintCallable, Category = Behavior)
	void FindTarget(); //사용하지 않음.

	UFUNCTION(BlueprintCallable, Category = Behavior)
	void FindRandomPos();

	UFUNCTION(BlueprintCallable, Category = Behavior)
	bool TargetCheck();

	UFUNCTION(BlueprintCallable, Category = Behavior)
	void SetBlackBoardMonsterState(E_MONSTER_STATE NewState);

public:
	virtual void Possess(APawn* InPawn) override;
	virtual void UpdateControlRotation(float DeltaTime, bool bUpdatePawn = true) override;

protected:
	virtual void BeginPlay() override;

public:
	AHT_MonsterAIController(const class FObjectInitializer& ObjectInitializer);
	AHT_MonsterAIController();
};