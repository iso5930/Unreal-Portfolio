// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "HT_BaseMonster.generated.h"

UENUM(BlueprintType)
enum class E_MONSTER_STATE : uint8
{
	MONSTER_STATE_IDLE		UMETA(DisplayName = "MONSTER_IDLE"),
	MONSTER_STATE_CHASE		UMETA(DisplayName = "MONSTER_CHASE"),
	MONSTER_STATE_ATTACK	UMETA(DisplayName = "MONSTER_ATTACK"),
	MONSTER_STATE_DIE		UMETA(DisplayName = "MONSTER_DIE")
};

UCLASS()
class HUNTER_API AHT_BaseMonster : public ACharacter
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = Behavior)
	class UBehaviorTree* BotBehavior;

	UPROPERTY(VisibleAnywhere, Category = PawnSensing)
	class UPawnSensingComponent* PawnSensing;

	UPROPERTY(BlueprintReadWrite)
	FString MonsterName;

	UAnimMontage* Attack_Montage;

	UAnimMontage* TrollAttack_MontageA;
	UAnimMontage* TrollAttack_MontageB;
	UAnimMontage* TrollAttack_MontageC;

public:
	UPROPERTY(Replicated)
	E_MONSTER_STATE MonsterState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxHealth;

	float DeathTime;

public:
	// Sets default values for this pawn's properties
	AHT_BaseMonster();

public:
	UFUNCTION()
	void OnSeePlayer(APawn* InPawn);

public:
	UFUNCTION(BlueprintCallable)
	E_MONSTER_STATE GetMonsterState();

	UFUNCTION(BlueprintCallable)
	void SetMonsterState(E_MONSTER_STATE NewState);

public:
	virtual void FaceRotation(FRotator NewControlRotation, float DeltaTime = 0.f) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

public:
	UFUNCTION(NetMulticast, Reliable)
	void ClientTakeDamege(float NewHp);

	void ClientTakeDamege_Implementation(float NewHp);

	UFUNCTION(NetMulticast, Reliable)
	void MonsterAttack();

	void MonsterAttack_Implementation();

	UFUNCTION(NetMulticast, Reliable)
	void Troll_Attack(int Num);

	void Troll_Attack_Implementation(int Num);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};