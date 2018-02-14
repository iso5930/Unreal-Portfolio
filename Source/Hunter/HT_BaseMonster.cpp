// Fill out your copyright notice in the Description page of Project Settings.

#include "Hunter.h"
#include "HT_BaseMonster.h"
#include "HT_MonsterAIController.h"
#include "Runtime/AIModule/Classes/Perception/PawnSensingComponent.h"
#include "UnrealNetwork.h"
#include "HT_GameInstance.h"
#include "HT_MonsterHpWidget.h"

// Sets default values
AHT_BaseMonster::AHT_BaseMonster()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;//false;

	bUseControllerRotationYaw = true;

	AIControllerClass = AHT_MonsterAIController::StaticClass();

	PawnSensing = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensing"));
	PawnSensing->SensingInterval = 0.25f;

	PawnSensing->OnSeePawn.AddDynamic(this, &AHT_BaseMonster::OnSeePlayer);

	MonsterState = E_MONSTER_STATE::MONSTER_STATE_IDLE;

	Health = 600.0f;

	DeathTime = 0.0f;

	ConstructorHelpers::FObjectFinder<UAnimMontage> AnimMontage1(TEXT("/Game/Monster/Bear/Animations/Montage/Bear_MeleeAttack"));

	if (AnimMontage1.Object != NULL)
	{
		Attack_Montage = AnimMontage1.Object;

		UE_LOG(LogClass, Warning, TEXT("%s"), TEXT("베어 불러오기 성공"));
	}

	//Bear_MeleeAttack
}

void AHT_BaseMonster::OnSeePlayer(APawn* InPawn)
{
	if (MonsterState == E_MONSTER_STATE::MONSTER_STATE_IDLE)
	{
		AHT_MonsterAIController* AIController = Cast<AHT_MonsterAIController>(GetController());

		if (AIController != NULL)
		{
			AIController->SetBlackBoardMonsterState(E_MONSTER_STATE::MONSTER_STATE_CHASE);
			AIController->SetTarget(InPawn);
		}
	}
}

E_MONSTER_STATE AHT_BaseMonster::GetMonsterState()
{
	return MonsterState;
}

void AHT_BaseMonster::SetMonsterState(E_MONSTER_STATE NewState)
{
	MonsterState = NewState;
}

void AHT_BaseMonster::FaceRotation(FRotator NewControlRotation, float DeltaTime /*= 0.f*/)
{
	FRotator CurrentRot = FMath::RInterpTo(GetActorRotation(), NewControlRotation, DeltaTime, 8.0f);

	Super::FaceRotation(CurrentRot, DeltaTime);
}

void AHT_BaseMonster::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AHT_BaseMonster, MonsterState);
}

float AHT_BaseMonster::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (GetWorld()->IsServer())
	{
		Health = Health - Damage;

		if (Health <= 0)
		{
			Health = 0;

			AHT_MonsterAIController* AIController = Cast<AHT_MonsterAIController>(GetController());

			if (AIController != NULL)
			{
				AIController->SetBlackBoardMonsterState(E_MONSTER_STATE::MONSTER_STATE_DIE);
				AIController->SetTarget(NULL);
			}

			//Destroy();
		}

		UE_LOG(LogClass, Warning, TEXT("%s"), TEXT("서버 충돌 함수"));

		ClientTakeDamege(Health);
	}

	return 0.0f;
}

void AHT_BaseMonster::ClientTakeDamege_Implementation(float NewHp)
{
	if (GetWorld()->IsClient())
	{
		if (NewHp <= 0)
		{
			AHT_MonsterAIController* AIController = Cast<AHT_MonsterAIController>(GetController());

			if (AIController != NULL)
			{
				AIController->SetBlackBoardMonsterState(E_MONSTER_STATE::MONSTER_STATE_DIE);
				AIController->SetTarget(NULL);
			}
		}

		UE_LOG(LogClass, Warning, TEXT("%s %f"), TEXT("몬스터 남은 체력"), NewHp);

		//소유중인 클라이언트에서 실행으로 나중에 바꾸기.

		UHT_GameInstance* GameInst = Cast<UHT_GameInstance>(GetWorld()->GetGameInstance());

		GameInst->MonsterHpWidget->SetVisibility(ESlateVisibility::Visible);
		GameInst->MonsterHpWidget->MonsterTakeDamege(this, Health, NewHp, FString("Bear"), NULL);

		Health = NewHp;
	}
}

void AHT_BaseMonster::MonsterAttack_Implementation()
{
	if (Attack_Montage != NULL)
	{
		PlayAnimMontage(Attack_Montage);
	}
}

// Called when the game starts or when spawned
void AHT_BaseMonster::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AHT_BaseMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GetWorld()->IsServer() && MonsterState == E_MONSTER_STATE::MONSTER_STATE_DIE)
	{
		DeathTime += DeltaTime;

		/*
		
		//나중에 Alpha로 서서히 사라지도록..

		*/

		if (DeathTime >= 5.0f)
			Destroy();
	}
}