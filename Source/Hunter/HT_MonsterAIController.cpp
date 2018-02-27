// Fill out your copyright notice in the Description page of Project Settings.

#include "Hunter.h"
#include "HT_MonsterAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Tasks/BTTask_BlueprintBase.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "AI/Navigation/NavigationSystem.h"
#include "HT_BaseCharacter.h"

void AHT_MonsterAIController::SetTarget(APawn* InTarget)
{
	if (BlackboardComponent != NULL)
	{
		BlackboardComponent->SetValue<UBlackboardKeyType_Object>(EnemyKeyID, InTarget);
		SetFocus(InTarget);
	}
}

void AHT_MonsterAIController::FindTarget()
{
	APawn* pMonster = GetPawn();

	if (pMonster != NULL)
	{
		const FVector Pos = pMonster->GetActorLocation();

		float BestDist = 9999999999.f;

		AHT_BaseCharacter* pBestTarget = NULL;

		FConstPawnIterator Iter = GetWorld()->GetPawnIterator();

		for (; Iter; ++Iter)
		{
			AHT_BaseCharacter* pTarget = Cast<AHT_BaseCharacter>(*Iter);

			if (pTarget != NULL)
			{
				float Dist = (pTarget->GetActorLocation() - Pos).SizeSquared();

				if (Dist < BestDist)
				{
					BestDist = Dist;
					pBestTarget = pTarget;
				}
			}
		}

		if (pBestTarget != NULL)
		{
			SetTarget(pBestTarget);
		}
	}
}

void AHT_MonsterAIController::FindRandomPos()
{
	APawn* pPawn = GetPawn();

	if (pPawn != NULL)
	{
		BlackboardComponent->SetValueAsVector(TEXT("StartPos"), pPawn->GetActorLocation());

		FVector EndPoint = UNavigationSystem::GetRandomPointInNavigableRadius(pPawn, pPawn->GetActorLocation(), 1000.f);

		BlackboardComponent->SetValueAsVector(TEXT("EndPos"), EndPoint);
	}
}

bool AHT_MonsterAIController::TargetCheck()
{
	if (BlackboardComponent != NULL)
	{
		UObject* pObj = BlackboardComponent->GetValue<UBlackboardKeyType_Object>(EnemyKeyID);

		if (pObj != NULL)
		{
			return true;
		}
		else
		{
			SetBlackBoardMonsterState(E_MONSTER_STATE::MONSTER_STATE_IDLE);

			return false;
		}
	}
	else
	{
		SetBlackBoardMonsterState(E_MONSTER_STATE::MONSTER_STATE_IDLE);

		return false;
	}
}

void AHT_MonsterAIController::SetBlackBoardMonsterState(E_MONSTER_STATE NewState)
{
	APawn* pPawn = GetPawn();

	if (pPawn != NULL)
	{
		AHT_BaseMonster* pMonster = Cast<AHT_BaseMonster>(pPawn);

		if (pMonster != NULL)
		{
			pMonster->SetMonsterState(NewState);
			BlackboardComponent->SetValueAsEnum(TEXT("MonsterState"), (uint8)NewState);
		}
	}
}

void AHT_MonsterAIController::MonsterAttack01()
{
	AHT_BaseMonster* pMonster = Cast<AHT_BaseMonster>(GetPawn());

	if (pMonster != NULL)
	{
		pMonster->MonsterAttack();
	}
}

void AHT_MonsterAIController::MonsterAttack02()
{
	AHT_BaseMonster* pMonster = Cast<AHT_BaseMonster>(GetPawn());

	if (pMonster != NULL)
	{
		//·£´ý °ª ¼³Á¤.

		int Num = (int)FMath::RandRange(0.0f, 2.9f);

		pMonster->Troll_Attack(Num);
		
		if (Num == 2)
		{
			BlackboardComponent->SetValueAsFloat(TEXT("WaitTime"), 4.2f);
		}
		else
		{
			BlackboardComponent->SetValueAsFloat(TEXT("WaitTime"), 2.3f);
		}
	}
}

E_MONSTER_STATE AHT_MonsterAIController::GetBlackBoardMonsterState()
{
	return (E_MONSTER_STATE)BlackboardComponent->GetValueAsEnum(TEXT("MonsterState"));
}

void AHT_MonsterAIController::Possess(APawn* InPawn)
{
	Super::Possess(InPawn);

	AHT_BaseMonster* pMonster = Cast<AHT_BaseMonster>(InPawn);

	if (pMonster != NULL)
	{
		if (pMonster->BotBehavior)
		{
			if (pMonster->BotBehavior->BlackboardAsset)
			{
				BlackboardComponent->InitializeBlackboard(*pMonster->BotBehavior->BlackboardAsset);
			}

			EnemyKeyID = BlackboardComponent->GetKeyID("Target");

			BehaviorComponent->StartTree(*(pMonster->BotBehavior));
		}
	}
}

void AHT_MonsterAIController::UpdateControlRotation(float DeltaTime, bool bUpdatePawn /*= true*/)
{
	FVector FocalPoint = GetFocalPoint();

	APawn* pPawn = GetPawn();

	bool bCheck = FocalPoint.IsZero();

	if (!bCheck && pPawn)
	{
		FVector Dir = FocalPoint - pPawn->GetActorLocation();
		FRotator Rotation = Dir.Rotation();
		Rotation.Yaw = FRotator::ClampAxis(Rotation.Yaw);
		SetControlRotation(Rotation);

		if (pPawn && bUpdatePawn)
		{
			pPawn->FaceRotation(Rotation, DeltaTime);
		}
	}
}

void AHT_MonsterAIController::BeginPlay()
{
	Super::BeginPlay();
}

AHT_MonsterAIController::AHT_MonsterAIController(const class FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;

	BlackboardComponent = ObjectInitializer.CreateDefaultSubobject<UBlackboardComponent>(this, TEXT("BlackbordComponent"));
	BrainComponent = BehaviorComponent = ObjectInitializer.CreateDefaultSubobject<UBehaviorTreeComponent>(this, TEXT("BehaviorComponent"));
}

AHT_MonsterAIController::AHT_MonsterAIController()
	:Super()
{
	PrimaryActorTick.bCanEverTick = true;

	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackbordComponent"));
	BrainComponent = BehaviorComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorComponent"));
}