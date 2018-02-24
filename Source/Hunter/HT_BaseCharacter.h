// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "HT_DropItem.h"
#include "HT_BaseWeapon.h"
#include "HT_BaseCharacter.generated.h"

UENUM(BlueprintType)
enum class E_PLAYER_STATE : uint8
{
	PLAYER_STATE_IDLE UMETA(DisplayName = "PLAYER_IDLE"),
	PLAYER_STATE_RUN UMETA(DisplayName = "PLAYER_RUN"),
	PLAYER_STATE_ATTACK01 UMETA(DisplayName = "PLAYER_ATTACK01"),
	PLAYER_STATE_ATTACK02 UMETA(DisplayName = "PLAYER_ATTACK02"),
	PLAYER_STATE_ATTACK03 UMETA(DisplayName = "PLAYER_ATTACK03"),
	PLAYER_STATE_ATTACK04 UMETA(DisplayName = "PLAYER_ATTACK04"),
	PLAYER_STATE_HIT UMETA(DisplayName = "HIT")
};

UCLASS()
class HUNTER_API AHT_BaseCharacter : public ACharacter
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Collision, meta = (AllowPrivateAccess = "true"))
	UBoxComponent* AttackCollision_01;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Collision, meta = (AllowPrivateAccess = "true"))
	UBoxComponent* AttackCollision_02;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Collision, meta = (AllowPrivateAccess = "true"))
	UBoxComponent* AttackCollision_03;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Collision, meta = (AllowPrivateAccess = "true"))
	UBoxComponent* AttackCollision_04;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Clothing, meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* UpperMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Clothing, meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* LowerMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Clothing, meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* FootMesh;

private:
	TArray<class AHT_DropItem*> DropItemArr;

	class AHT_BaseNPC* OverlapNPC;

	E_PLAYER_STATE CurPlayerState;

	TArray<FItem_Info> TakeItemList;

	FString CharacterName; //캐릭터 닉네임 동기화 전용.

	TArray<int> EquipList; //장비 동기화 전용.  //Upper, Lower, Foot

	bool IsNetworkCharacter = true;
	bool IsBeginPlay = false;

	float AccTime = 0.0f;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Weapon)
	FName WeaponAttachPointName;

	UPROPERTY(BlueprintReadWrite)
	class AHT_BaseWeapon* Weapon;

	UPROPERTY(BlueprintReadWrite)
	class UHT_UserNameWidget* UserNameWidget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class UParticleSystem* AttackEffect;

	float Health;
	float MaxHealth;

	float Mana;
	float MaxMana;

	class AHT_BaseWeapon* SubWeapon;
	
	UPROPERTY(BlueprintReadWrite)
	bool IsWeaponChange = false; //무기 동기화때문에 사용함.

	FString ChangeWeaponName;
	FString ChangeSubWeaponName;
	FItem_Info ChangeWeaponInfo;
	int PlayerNum = -1;

	UPROPERTY(BlueprintReadWrite)
	float AttackRange = 0.0f;

	UPROPERTY(BlueprintReadWrite)
	bool IsSphere = false;
	
public:
	// Sets default values for this character's properties
	AHT_BaseCharacter();

public:
	void MoveForward(float Value);
	void MoveRight(float Value);
	void Zoom(float Value);

public:
	void OnInventoryWidget();
	void OnEquipInventoryWidget();
	void Attack();
	void StrongAttack();
	void OnInputTextWidget();

public:
	void OnTestFunction();

public:
	FName GetWeaponAttachPointName() const;
	void WeaponChange(FItem_Info NewWeaponInfo);
	void EquipChange(FItem_Info NewEquip);
	void DetachEquip(E_ITEM_TYPE Equip_Type);
	void LoadEquip(TArray<FItem_Info> LoadEquipData);

public:
	UFUNCTION(BlueprintCallable)
	void SetPlayerState(E_PLAYER_STATE NewPlayerState);

	UFUNCTION(BlueprintCallable)
	E_PLAYER_STATE GetCurPlayerState();

	UFUNCTION(BlueprintCallable)
	void AttackBegin();

	UFUNCTION(BlueprintCallable)
	void AttackEnd();

	UFUNCTION(BlueprintCallable)
	void ShowLog(FString Log);

public:
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappingComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappingComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(BlueprintCallable)
	void OnWeaponAttackOverlap(class UPrimitiveComponent* OverlappingComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(Server, Reliable, WithValidation)
	void SpawnWeapon(FItem_Info NewWeaponInfo);

	virtual void SpawnWeapon_Implementation(FItem_Info NewWeaponInfo);

	bool SpawnWeapon_Validate(FItem_Info NewWeaponInfo);

	UFUNCTION(NetMulticast, Reliable)
	void AttatchWeapon(FItem_Info WeaponInfo, const FString& SpawnWeaponName, const FString& SpawnSubWeaponName = FString());

	virtual void AttatchWeapon_Implementation(FItem_Info WeaponInfo, const FString& SpawnWeaponName, const FString& SpawnSubWeaponName = FString());

	UFUNCTION(Server, Reliable, WithValidation)
	void BeginAttack();

	virtual void BeginAttack_Implementation();

	bool BeginAttack_Validate();

	UFUNCTION(Server, Reliable, WithValidation)
	void BeginStrongAttack();

	virtual void BeginStrongAttack_Implementation();

	bool BeginStrongAttack_Validate();

	UFUNCTION(BlueprintCallable)
	void PointDamage(float Damage);

	UFUNCTION(Client, Reliable)
	void ClientPointDamege(float NewHealth);

	virtual void ClientPointDamege_Implementation(float NewHealth);

	UFUNCTION(Server, Reliable, WithValidation)
	void DestroyWeapon();

	virtual void DestroyWeapon_Implementation();

	bool DestroyWeapon_Validate();

	UFUNCTION(Client, Reliable)
	void AddItem(FItem_Info Info);

	virtual void AddItem_Implementation(FItem_Info Info);

	UFUNCTION(Server, Reliable, WithValidation)
	void EquipChange_Server(FItem_Info NewEquip);

	virtual void EquipChange_Server_Implementation(FItem_Info NewEquip);

	bool EquipChange_Server_Validate(FItem_Info NewEquip);

	UFUNCTION(NetMulticast, Reliable)
	void EquipChange_Client(FItem_Info NewEquip);

	virtual void EquipChange_Client_Implementation(FItem_Info NewEquip);

	UFUNCTION(Server, Reliable, WithValidation)
	void DetachEquip_Server(E_ITEM_TYPE Equip_Type);

	virtual void DetachEquip_Server_Implementation(E_ITEM_TYPE Equip_Type);

	bool DetachEquip_Server_Validate(E_ITEM_TYPE Equip_Type);

	UFUNCTION(NetMulticast, Reliable)
	void DetachEquip_Client(E_ITEM_TYPE Equip_Type);

	virtual void DetachEquip_Client_Implementation(E_ITEM_TYPE Equip_Type);

	UFUNCTION(Server, Reliable, WithValidation)
	void ReflashCharacter_Server(const FString& PlayerName, const TArray<int>& Equip);

	virtual void ReflashCharacter_Server_Implementation(const FString& PlayerName, const TArray<int>& Equip);

	bool ReflashCharacter_Server_Validate(const FString& PlayerName, const TArray<int>& Equip);

	UFUNCTION(NetMulticast, Reliable)
	void ReflashCharacter_Client(const FString& PlayerName, const TArray<int>& Equip);

	virtual void ReflashCharacter_Client_Implementation(const FString& PlayerName, const TArray<int>& Equip);

	UFUNCTION(Client, Reliable)
	void OnMonsterWidget(const FString& MonsterName, float HP, float MaxHP);

	virtual void OnMonsterWidget_Implementation(const FString& MonsterName, float HP, float MaxHP);

	UFUNCTION(BlueprintCallable, NetMulticast, Reliable)
	void RenderHitEffect();

	virtual void RenderHitEffect_Implementation();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};