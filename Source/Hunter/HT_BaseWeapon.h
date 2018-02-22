// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "HT_BaseWeapon.generated.h"

UENUM(BlueprintType)
enum class E_WEAPON_TYPE : uint8
{
	WEAPON_SCYTHE UMETA(DisplayName = "WEAPON_SCYTHE"),
	WEAPON_DUAL_BLADE UMETA(DisplayName = "WEAPON_DUAL_BLADE"),
	WEAPON_NONE UMETA(DisplayName = "WEAPON_NONE")
};

UCLASS()
class HUNTER_API AHT_BaseWeapon : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleDefaultsOnly)
	USkeletalMeshComponent* WeaponMesh;

public:
	E_WEAPON_TYPE WeaponType;
	class AHT_BaseCharacter* OwnerCharacter;

protected:
	UAnimMontage* Attack01_Montage;
	UAnimMontage* Attack02_Montage;
	UAnimMontage* Attack03_Montage;
	UAnimMontage* Attack04_Montage;
	
	UAnimMontage* StrongAttack01_Montage;
	UAnimMontage* StrongAttack02_Montage;
	UAnimMontage* StrongAttack03_Montage;
	UAnimMontage* StrongAttack04_Montage;

protected:
	int32 WeaponIndex;
	bool IsNextAttack;

public:
	UPROPERTY(Replicated)
	int RealIndex; //서버 동기화 때문에..

	UPROPERTY(Replicated)
	int OwnerCharacterNum;
	
public:	
	// Sets default values for this actor's properties
	AHT_BaseWeapon();

public:
	bool SetWeaponIndex(int32 Index);
	void SetWeaponType(E_WEAPON_TYPE NewType);

public:
	void AttachMeshToPawn(FName AttachName);

public:
	UFUNCTION(BlueprintCallable)
	E_WEAPON_TYPE GetWeaponType();

	UFUNCTION(BlueprintCallable)
	void SetNextAttack(bool NextAttack);

public:
	void FindOwenrCharacter(int OwnerNum);
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	UFUNCTION(NetMulticast, Reliable)
	void Attack();

	virtual void Attack_Implementation();

	UFUNCTION(NetMulticast, Reliable)
	void StrongAttack();

	virtual void StrongAttack_Implementation();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};