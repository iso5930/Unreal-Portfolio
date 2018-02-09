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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Widget, meta = (AllowPrivateAccess = "true"))
	class UWidgetComponent* UserNameWidget;

	UPROPERTY(EditDefaultsOnly, Category = Weapon)
	TSubclassOf<class AHT_BaseWeapon> TestWeaponClass;

private:
	TArray<class AHT_DropItem*> DropItemArr;

	class AHT_BaseNPC* OverlapNPC;

	E_PLAYER_STATE PlayerState;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Weapon)
	FName WeaponAttachPointName;

	UPROPERTY(BlueprintReadWrite)
	class AHT_BaseWeapon* Weapon;

	class AHT_BaseWeapon* SubWeapon;
	
	UPROPERTY(BlueprintReadWrite)
	bool IsWeaponChange = false; //무기 동기화때문에 사용함.

	FString ChangeWeaponName;
	FString ChangeSubWeaponName;
	FItem_Info ChangeWeaponInfo;
	
public:
	// Sets default values for this character's properties
	AHT_BaseCharacter();

public:
	void MoveForward(float Value);
	void MoveRight(float Value);

public:
	void OnInventoryWidget();
	void Attack();
	void Test();
	void Action_ItemTake();

	void OnInputTextWidget();

public:
	void OnTestFunction();

public:
	FName GetWeaponAttachPointName() const;
	void WeaponChange(FItem_Info NewWeaponInfo);

public:
	UFUNCTION(BlueprintCallable)
	void SetPlayerState(E_PLAYER_STATE NewPlayerState);

	UFUNCTION(BlueprintCallable)
	E_PLAYER_STATE GetPlayerState();

public:
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappingComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappingComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(Server, Reliable, WithValidation)
	void SpawnWeapon(FItem_Info NewWeaponInfo);

	virtual void SpawnWeapon_Implementation(FItem_Info NewWeaponInfo);

	bool SpawnWeapon_Validate(FItem_Info NewWeaponInfo);

	/*UFUNCTION(Client, unreliable)
	void SetWeaponName(const TCHAR _WeaponName, const TCHAR _SubWeaponName);

	virtual void SetWeaponName_Implementation(const TCHAR _WeaponName, const TCHAR _SubWeaponName);*/

	UFUNCTION(NetMulticast, Reliable)
	void AttatchWeapon(FItem_Info WeaponInfo, const FString& SpawnWeaponName, const FString& SpawnSubWeaponName = FString());

	virtual void AttatchWeapon_Implementation(FItem_Info WeaponInfo, const FString& SpawnWeaponName, const FString& SpawnSubWeaponName = FString());


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};