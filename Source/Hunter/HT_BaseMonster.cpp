// Fill out your copyright notice in the Description page of Project Settings.

#include "Hunter.h"
#include "HT_BaseMonster.h"
#include "HT_MonsterAIController.h"
#include "Runtime/AIModule/Classes/Perception/PawnSensingComponent.h"
#include "UnrealNetwork.h"

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
			UE_LOG(LogClass, Warning, TEXT("%s"), TEXT("캐스팅 실패!"));
		}

		UE_LOG(LogClass, Warning, TEXT("%s"), TEXT("플레이어 인식, 추적으로 상태 변환"));
	}

	UE_LOG(LogClass, Warning, TEXT("%s"), TEXT("플레이어 인식"));
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
	UE_LOG(LogClass, Warning, TEXT("%s"), TEXT("몬스터 Take Damege 호출"));

	return 0.0f;
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