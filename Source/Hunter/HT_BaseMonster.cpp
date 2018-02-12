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
	PrimaryActorTick.bCanEverTick = false;

	bUseControllerRotationYaw = true;

	AIControllerClass = AHT_MonsterAIController::StaticClass();

	PawnSensing = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensing"));
	PawnSensing->SensingInterval = 0.25f;

	PawnSensing->OnSeePawn.AddDynamic(this, &AHT_BaseMonster::OnSeePlayer);

	MonsterState = E_MONSTER_STATE::MONSTER_STATE_IDLE;

	Health = 30000.0f;
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
		else
		{
			//UE_LOG(LogClass, Warning, TEXT("%s"), TEXT("ĳ���� ����!"));
		}

		//UE_LOG(LogClass, Warning, TEXT("%s"), TEXT("�÷��̾� �ν�, �������� ���� ��ȯ"));
	}

	//UE_LOG(LogClass, Warning, TEXT("%s"), TEXT("�÷��̾� �ν�"));
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

			SetMonsterState(E_MONSTER_STATE::MONSTER_STATE_DIE);

			Destroy();
		}

		UE_LOG(LogClass, Warning, TEXT("%s"), TEXT("���� �浹 �Լ�"));

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
			SetMonsterState(E_MONSTER_STATE::MONSTER_STATE_DIE);
		}

		UE_LOG(LogClass, Warning, TEXT("%s %f"), TEXT("���� ���� ü��"), NewHp);

		//�������� Ŭ���̾�Ʈ���� �������� ���߿� �ٲٱ�.

		UHT_GameInstance* GameInst = Cast<UHT_GameInstance>(GetWorld()->GetGameInstance());

		GameInst->MonsterHpWidget->SetVisibility(ESlateVisibility::Visible);
		GameInst->MonsterHpWidget->MonsterTakeDamege(this, Health, NewHp, FString("Bear"), NULL);

		Health = NewHp;
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
}