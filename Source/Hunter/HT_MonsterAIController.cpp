// Fill out your copyright notice in the Description page of Project Settings.

#include "Hunter.h"
#include "HT_MonsterAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Tasks/BTTask_BlueprintBase.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "HT_BaseMonster.h"
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

	UE_LOG(LogClass, Warning, TEXT("%s"), TEXT("Find Target"));

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

void AHT_MonsterAIController::Possess(APawn* InPawn)
{
	Super::Possess(InPawn);

	AHT_BaseMonster* pMonster = Cast<AHT_BaseMonster>(InPawn);

	UE_LOG(LogClass, Warning, TEXT("%s"), TEXT("Possess 65"));

	if (pMonster != NULL)
	{
		if (pMonster->BotBehavior)
		{
			if (pMonster->BotBehavior->BlackboardAsset)
			{
				if (BlackboardComponent->InitializeBlackboard(*pMonster->BotBehavior->BlackboardAsset))
				{
					UE_LOG(LogClass, Warning, TEXT("%s"), TEXT("초기화 성공"));
				}
				else
				{
					UE_LOG(LogClass, Warning, TEXT("%s"), TEXT("초기화 실패"));
				}
			}

			EnemyKeyID = BlackboardComponent->GetKeyID("Target");

			BehaviorComponent->StartTree(*(pMonster->BotBehavior));

			UE_LOG(LogClass, Warning, TEXT("%s"), TEXT("Possess 82"));
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

		UE_LOG(LogClass, Warning, TEXT("%s"), TEXT("UpDate Rot 11"));

		if (pPawn && bUpdatePawn)
		{
			pPawn->FaceRotation(Rotation, DeltaTime);

			UE_LOG(LogClass, Warning, TEXT("%s"), TEXT("UpDate Rot 12"));
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