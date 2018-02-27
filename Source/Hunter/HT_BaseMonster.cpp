// Fill out your copyright notice in the Description page of Project Settings.

#include "Hunter.h"
#include "HT_BaseMonster.h"
#include "HT_MonsterAIController.h"
#include "Runtime/AIModule/Classes/Perception/PawnSensingComponent.h"
#include "UnrealNetwork.h"
#include "HT_GameInstance.h"
#include "HT_MonsterHpWidget.h"
#include "HT_BaseCharacter.h"
#include "HT_DamegeEffect.h"

// Sets default values
AHT_BaseMonster::AHT_BaseMonster()
{
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationYaw = true;

	AIControllerClass = AHT_MonsterAIController::StaticClass();

	PawnSensing = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensing"));
	PawnSensing->SensingInterval = 0.25f;
	PawnSensing->OnSeePawn.AddDynamic(this, &AHT_BaseMonster::OnSeePlayer);
	
	MonsterState = E_MONSTER_STATE::MONSTER_STATE_IDLE;

	Health = 600.0f;
	MaxHealth = 600.0f;

	DeathTime = 0.0f;

	ConstructorHelpers::FObjectFinder<UAnimMontage> AnimMontage1(TEXT("/Game/Monster/Bear/Animations/Montage/Bear_MeleeAttack"));

	if (AnimMontage1.Object != NULL)
	{
		Attack_Montage = AnimMontage1.Object;
	}

	ConstructorHelpers::FObjectFinder<UAnimMontage> AnimMontage2(TEXT("/Game/Monster/Troll/Animations/Montage/Troll_AttackA01_Montage"));

	if (AnimMontage2.Object != NULL)
	{
		TrollAttack_MontageA = AnimMontage2.Object;
	}

	ConstructorHelpers::FObjectFinder<UAnimMontage> AnimMontage3(TEXT("/Game/Monster/Troll/Animations/Montage/Troll_AttackA02_Montage"));

	if (AnimMontage3.Object != NULL)
	{
		TrollAttack_MontageB = AnimMontage3.Object;
	}

	ConstructorHelpers::FObjectFinder<UAnimMontage> AnimMontage4(TEXT("/Game/Monster/Troll/Animations/Montage/Troll_AttackA03_Montage"));

	if (AnimMontage4.Object != NULL)
	{
		TrollAttack_MontageC = AnimMontage4.Object;
	}
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
		float NewHP = Health - Damage;

		UHT_GameInstance* GameInstance = Cast<UHT_GameInstance>(GetWorld()->GetGameInstance());

		AHT_BaseCharacter* pPlayer = Cast<AHT_BaseCharacter>(DamageCauser);

		if (NewHP <= 0)
		{
			NewHP = 0;

			AHT_MonsterAIController* AIController = Cast<AHT_MonsterAIController>(GetController());

			if (AIController != NULL)
			{
				AIController->SetBlackBoardMonsterState(E_MONSTER_STATE::MONSTER_STATE_DIE);
				AIController->SetTarget(NULL);
			}

			if (pPlayer != NULL && GameInstance != NULL)
			{
				bool IsEquip = (int)FMath::RandRange(0.0f, 10.0f) % 2;

				if (IsEquip)
				{
					int ItemNum = (int)FMath::RandRange(8.0f, 16.9f);

					pPlayer->AddItem(GameInstance->Item_DataBase[ItemNum]);
				}

				int ItemNum = (int)FMath::RandRange(0.0f, 5.9f);

				pPlayer->AddItem(GameInstance->Item_DataBase[ItemNum]);
				pPlayer->AddExp(70);
			}
		}

		if (pPlayer != NULL && GameInstance != NULL)
		{
			pPlayer->OnMonsterWidget(MonsterName, NewHP, MaxHealth);

			OnSeePlayer(pPlayer);
		}

		if (DamegeEffect != NULL)
		{
			float Dist = 20.0f;

			if (MonsterName != "Bear")
			{
				Dist = 40.0f;
			}

			FVector SpawnLocal = GetActorLocation() + GetActorUpVector() * Dist;
			FRotator SpawnRotation = GetActorRotation();

			AHT_DamegeEffect* SpawnEffect = GetWorld()->SpawnActor<AHT_DamegeEffect>(DamegeEffect, SpawnLocal, SpawnRotation);

			if (SpawnEffect != NULL)
			{
				SpawnEffect->Damege = Damage;
			}
		}

		Health = NewHP;

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

		if (AttackEffect != NULL)
		{
			FVector EffectPos = GetActorForwardVector() * 30.0f + GetActorLocation();

			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), AttackEffect, EffectPos);
		}

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

void AHT_BaseMonster::Troll_Attack_Implementation(int Num)
{
	switch (Num)
	{
	case 0:

		if (TrollAttack_MontageA != NULL)
		{
			PlayAnimMontage(TrollAttack_MontageA);
		}

		break;

	case 1:

		if (TrollAttack_MontageB != NULL)
		{
			PlayAnimMontage(TrollAttack_MontageB);
		}

		break;

	case 2:

		if (TrollAttack_MontageC != NULL)
		{
			PlayAnimMontage(TrollAttack_MontageC);
		}

		break;
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
		
		//나중에 Alpha로 서서히 사라지도록.. //트롤과 베어의 시간이 다르다..

		*/

		if (DeathTime >= 5.0f)
			Destroy();
	}
}