// Fill out your copyright notice in the Description page of Project Settings.

#include "Hunter.h"
#include "HT_BaseCharacter.h"
#include "HT_GameInstance.h"
#include "HT_InventoryWidget.h"
#include "HT_DropItemWidget.h"
#include "HT_ChattingInputWidget.h"
#include "HT_BaseNPC.h"
#include "WidgetComponent.h"
#include "HT_UserNameWidget.h"
#include "ScrollBox.h"
#include "HT_BaseWeapon.h"
#include "HT_Weapon_Scythe.h"
#include "HT_Weapon_DualBlade.h"
#include "UnrealNetwork.h"
#include "HT_BaseMonster.h"
#include "HT_PlayerStateWidget.h"
#include "HT_StagePlayerState.h"
#include "HT_EquipInventory_Widget.h"
#include "HT_TakeItemWidget.h"
#include "HT_StageWidget.h"
#include "HT_MonsterHpWidget.h"

// Sets default values
AHT_BaseCharacter::AHT_BaseCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
	
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AHT_BaseCharacter::OnOverlapBegin);
	GetCapsuleComponent()->OnComponentEndOverlap.AddDynamic(this, &AHT_BaseCharacter::OnOverlapEnd);

	CurPlayerState = E_PLAYER_STATE::PLAYER_STATE_IDLE;

	AttackCollision_01 = CreateDefaultSubobject<UBoxComponent>(TEXT("AttackCollision_01"));
	AttackCollision_01->SetupAttachment(GetMesh());
	AttackCollision_01->SetActive(true);
	AttackCollision_01->bGenerateOverlapEvents = false;

	AttackCollision_02 = CreateDefaultSubobject<UBoxComponent>(TEXT("AttackCollision_02"));
	AttackCollision_02->SetupAttachment(GetMesh());
	AttackCollision_02->SetActive(true);
	AttackCollision_02->bGenerateOverlapEvents = false;

	AttackCollision_03 = CreateDefaultSubobject<UBoxComponent>(TEXT("AttackCollision_03"));
	AttackCollision_03->SetupAttachment(GetMesh());
	AttackCollision_03->SetActive(true);
	AttackCollision_03->bGenerateOverlapEvents = false;

	AttackCollision_04 = CreateDefaultSubobject<UBoxComponent>(TEXT("AttackCollision_04"));
	AttackCollision_04->SetupAttachment(GetMesh());
	AttackCollision_04->SetActive(true);
	AttackCollision_04->bGenerateOverlapEvents = false;

	USkeletalMeshComponent* pMesh = GetMesh();

	UpperMesh = CreateDefaultSubobject<USkeletalMeshComponent>("Upper_Mesh");
	UpperMesh->SetupAttachment(pMesh);
	UpperMesh->SetMasterPoseComponent(pMesh);

	LowerMesh = CreateDefaultSubobject<USkeletalMeshComponent>("Lower_Mesh");
	LowerMesh->SetupAttachment(pMesh);
	LowerMesh->SetMasterPoseComponent(pMesh);

	FootMesh = CreateDefaultSubobject<USkeletalMeshComponent>("Foot_Mesh");
	FootMesh->SetupAttachment(pMesh);
	FootMesh->SetMasterPoseComponent(pMesh);

	MaxHealth = 600.0f;
	Health = 600.0f;

	MaxMana = 200.0f;
	Mana = 200.0f;		
}

void AHT_BaseCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AHT_BaseCharacter::MoveRight(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void AHT_BaseCharacter::Zoom(float Value)
{
	if (Value != 0.0f)
	{
		CameraBoom->TargetArmLength -= Value;

		if (CameraBoom->TargetArmLength <= 25.0f)
		{
			CameraBoom->TargetArmLength = 25.0f;
		}
		else if (CameraBoom->TargetArmLength >= 200.0f)
		{
			CameraBoom->TargetArmLength = 200.0f;
		}
	}
}

void AHT_BaseCharacter::OnInventoryWidget()
{
	UHT_GameInstance* GameInstance = Cast<UHT_GameInstance>(GetWorld()->GetGameInstance());

	if (GameInstance != NULL)
	{
		if (GameInstance->UserInventoryWidget->GetVisibility() == ESlateVisibility::Visible)
		{
			GameInstance->UserInventoryWidget->SetVisibility(ESlateVisibility::Collapsed);

			if (GameInstance->EquipWidget->GetVisibility() == ESlateVisibility::Collapsed)
			{
				GetWorld()->GetFirstPlayerController()->bShowMouseCursor = false;
				GetWorld()->GetFirstPlayerController()->bEnableClickEvents = false;
			}
		}
		else
		{
			GameInstance->UserInventoryWidget->SetVisibility(ESlateVisibility::Visible);
			GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;
			GetWorld()->GetFirstPlayerController()->bEnableClickEvents = true;
		}
	}
}

void AHT_BaseCharacter::OnEquipInventoryWidget()
{
	UHT_GameInstance* GameInstance = Cast<UHT_GameInstance>(GetWorld()->GetGameInstance());

	if (GameInstance != NULL)
	{
		if (GameInstance->EquipWidget->GetVisibility() == ESlateVisibility::Visible)
		{
			GameInstance->EquipWidget->SetVisibility(ESlateVisibility::Collapsed);

			if (GameInstance->UserInventoryWidget->GetVisibility() == ESlateVisibility::Collapsed)
			{
				GetWorld()->GetFirstPlayerController()->bShowMouseCursor = false;
				GetWorld()->GetFirstPlayerController()->bEnableClickEvents = false;
			}
		}
		else
		{
			GameInstance->EquipWidget->SetVisibility(ESlateVisibility::Visible);
			GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;
			GetWorld()->GetFirstPlayerController()->bEnableClickEvents = true;
		}
	}
}

void AHT_BaseCharacter::Attack()
{
	if (Weapon != NULL)
	{
		BeginAttack();
	}
}

void AHT_BaseCharacter::StrongAttack()
{
	if (Weapon != NULL)
	{
		BeginStrongAttack();
	}
}

void AHT_BaseCharacter::OnInputTextWidget()
{
	UHT_GameInstance* GameInstance = Cast<UHT_GameInstance>(GetWorld()->GetGameInstance());

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

	if (GameInstance != NULL)
	{
		if (GameInstance->ChattingInputWidget->GetVisibility() == ESlateVisibility::Collapsed)
		{
			GameInstance->ChattingInputWidget->SetVisibility(ESlateVisibility::Visible);

			FInputModeUIOnly InputMode;

			UHT_ChattingInputWidget* InputWidget = Cast<UHT_ChattingInputWidget>(GameInstance->ChattingInputWidget);

			InputMode = InputMode.SetWidgetToFocus(InputWidget->InputWidget->GetCachedWidget());

			if (PlayerController != NULL)
			{
				PlayerController->SetInputMode(InputMode);

				UE_LOG(LogClass, Warning, TEXT("%s"), TEXT("포커스 셋팅"));
			}
		}
		else
		{
			GameInstance->ChattingInputWidget->SetVisibility(ESlateVisibility::Collapsed);
		}
	}
}

void AHT_BaseCharacter::OnTestFunction()
{
	/*if (OverlapNPC != NULL)
	{
		OverlapNPC->NPCMenuWidgetPopup();
	}*/
}

FName AHT_BaseCharacter::GetWeaponAttachPointName() const
{
	return WeaponAttachPointName;
}

void AHT_BaseCharacter::WeaponChange(FItem_Info NewWeaponInfo)
{
	SpawnWeapon(NewWeaponInfo);
}

void AHT_BaseCharacter::EquipChange(FItem_Info NewEquip)
{
	EquipChange_Server(NewEquip);
}

void AHT_BaseCharacter::DetachEquip(E_ITEM_TYPE Equip_Type)
{
	DetachEquip_Server(Equip_Type);
}

void AHT_BaseCharacter::LoadEquip(TArray<FItem_Info> LoadEquipData)
{
	for (int i = 0; i < LoadEquipData.Num(); ++i)
	{
		if (LoadEquipData[i].Item_Num != -1)
		{
			if (i < 3)
			{
				EquipChange(LoadEquipData[i]);
			}
			else
			{
				WeaponChange(LoadEquipData[i]);
			}
		}
	}
}

void AHT_BaseCharacter::SetPlayerState(E_PLAYER_STATE NewPlayerState)
{
	CurPlayerState = NewPlayerState;
}

E_PLAYER_STATE AHT_BaseCharacter::GetCurPlayerState()
{
	return CurPlayerState;
}

void AHT_BaseCharacter::AttackBegin()
{
	UE_LOG(LogClass, Warning, TEXT("%s"), TEXT("어택 비긴"));

	if (GetWorld()->IsServer())
	{
		switch (CurPlayerState)
		{
		case E_PLAYER_STATE::PLAYER_STATE_ATTACK01:

			AttackCollision_01->bGenerateOverlapEvents = true;
			AttackCollision_02->bGenerateOverlapEvents = false;
			AttackCollision_03->bGenerateOverlapEvents = false;
			AttackCollision_04->bGenerateOverlapEvents = false;

			break;

		case E_PLAYER_STATE::PLAYER_STATE_ATTACK02:

			AttackCollision_01->bGenerateOverlapEvents = false;
			AttackCollision_02->bGenerateOverlapEvents = true;
			AttackCollision_03->bGenerateOverlapEvents = false;
			AttackCollision_04->bGenerateOverlapEvents = false;

			break;

		case E_PLAYER_STATE::PLAYER_STATE_ATTACK03:

			AttackCollision_01->bGenerateOverlapEvents = false;
			AttackCollision_02->bGenerateOverlapEvents = false;
			AttackCollision_03->bGenerateOverlapEvents = true;
			AttackCollision_04->bGenerateOverlapEvents = false;

			break;

		case E_PLAYER_STATE::PLAYER_STATE_ATTACK04:

			AttackCollision_01->bGenerateOverlapEvents = false;
			AttackCollision_02->bGenerateOverlapEvents = false;
			AttackCollision_03->bGenerateOverlapEvents = false;
			AttackCollision_04->bGenerateOverlapEvents = true;

			break;
		}
	}
	else
	{
		UHT_GameInstance* GameInstance = Cast<UHT_GameInstance>(GetWorld()->GetGameInstance());
		AHT_StagePlayerState* StagePlayerStage = Cast<AHT_StagePlayerState>(PlayerState);

		if (GameInstance != NULL && StagePlayerStage != NULL)
		{
			if (GameInstance->PlayerNum == StagePlayerStage->ClientPlayerNum)
			{
				MoveForward(0.5f);
			}
		}
	}
}

void AHT_BaseCharacter::AttackEnd()
{
	UE_LOG(LogClass, Warning, TEXT("%s"), TEXT("어택 엔드"));

	if (GetWorld()->IsServer())
	{
		AttackCollision_01->bGenerateOverlapEvents = false;
		AttackCollision_02->bGenerateOverlapEvents = false;
		AttackCollision_03->bGenerateOverlapEvents = false;
		AttackCollision_04->bGenerateOverlapEvents = false;
	}
}	

void AHT_BaseCharacter::ShowLog(FString Log)
{
	UE_LOG(LogClass, Warning, TEXT("%s"), *Log);
}

void AHT_BaseCharacter::OnWeaponAttackOverlap(class UPrimitiveComponent* OverlappingComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (GetWorld()->IsServer() && OtherActor->IsA(AHT_BaseMonster::StaticClass()))
	{
		UE_LOG(LogClass, Warning, TEXT("%s"), TEXT("몬스터 충돌 피 깍임."));

		//데미지가 유동적으로 변하도록 바꾸자.

		UGameplayStatics::ApplyDamage(OtherActor, 60.0f, NULL, this, UDamageType::StaticClass());
	}
}

void AHT_BaseCharacter::OnOverlapBegin(class UPrimitiveComponent* OverlappingComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(AHT_DropItem::StaticClass()))
	{
		DropItemArr.Add((AHT_DropItem*)OtherActor);
	}
	else if (OtherActor->IsA(AHT_BaseNPC::StaticClass()) && GetWorld()->IsServer())
	{
		OverlapNPC = Cast<AHT_BaseNPC>(OtherActor);

		UE_LOG(LogClass, Warning, TEXT("%s"), TEXT("NPC Overlab"));
	}
}

void AHT_BaseCharacter::OnOverlapEnd(class UPrimitiveComponent* OverlappingComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->IsA(AHT_DropItem::StaticClass()))
	{
		DropItemArr.Remove((AHT_DropItem*)OtherActor);
	}
	else if (OtherActor->IsA(AHT_BaseNPC::StaticClass()))
	{
		OverlapNPC = NULL;
	}
}

void AHT_BaseCharacter::SpawnWeapon_Implementation(FItem_Info NewWeaponInfo)
{
	if (Weapon != NULL)
	{
		Weapon->Destroy();
		Weapon = NULL;
	}

	if (SubWeapon != NULL)
	{
		SubWeapon->Destroy();
		SubWeapon = NULL;
	}

	FRotator SpawnRotation(0.0f, 0.0f, 0.0f);
	FVector SpawnLocal(0.0f, 0.0f, 0.0f);

	AHT_BaseWeapon* pSpawnWeapon = NULL;
	AHT_BaseWeapon* pSpawnSubWeapon = NULL;

	UE_LOG(LogClass, Warning, TEXT("%s"), TEXT("Spawn Weapon()"));

	switch (NewWeaponInfo.Item_Type)
	{
	case E_ITEM_TYPE::ITEM_TYPE_WEAPON_SCYTHE:

		pSpawnWeapon = GetWorld()->SpawnActor<AHT_BaseWeapon>(AHT_Weapon_Scythe::StaticClass(), SpawnLocal, SpawnRotation);

		AttatchWeapon(NewWeaponInfo, pSpawnWeapon->GetName()); //클라이언트 호출로 바꾸기.

		if (GetWorld()->IsServer())
		{
			Weapon = pSpawnWeapon;
			Weapon->OwnerCharacter = this;
			Weapon->SetWeaponIndex(NewWeaponInfo.Item_Num);
			Weapon->SetWeaponType(E_WEAPON_TYPE::WEAPON_SCYTHE);
			Weapon->AttachMeshToPawn(TEXT("Scythe_RH"));
			Weapon->OwnerCharacterNum = PlayerNum;

			UE_LOG(LogClass, Warning, TEXT("%s"), TEXT("Is Server"));
		}
			
		break;

	case E_ITEM_TYPE::ITEM_TYPE_WEAPON_DUAL_BLADE:

		pSpawnWeapon = GetWorld()->SpawnActor<AHT_BaseWeapon>(AHT_Weapon_DualBlade::StaticClass(), SpawnLocal, SpawnRotation);
		pSpawnSubWeapon = GetWorld()->SpawnActor<AHT_BaseWeapon>(AHT_Weapon_DualBlade::StaticClass(), SpawnLocal, SpawnRotation);

		AttatchWeapon(NewWeaponInfo, pSpawnWeapon->GetName(), pSpawnSubWeapon->GetName());
		
		if (GetWorld()->IsServer())
		{
			Weapon = pSpawnWeapon;
			Weapon->OwnerCharacter = this;
			Weapon->SetWeaponIndex(NewWeaponInfo.Item_Num);
			Weapon->SetWeaponType(E_WEAPON_TYPE::WEAPON_DUAL_BLADE);
			Weapon->AttachMeshToPawn(TEXT("DualBlade_RH"));
			Weapon->OwnerCharacterNum = PlayerNum;

			SubWeapon = pSpawnSubWeapon;
			SubWeapon->OwnerCharacter = this;
			SubWeapon->SetWeaponIndex(NewWeaponInfo.Item_Num);
			SubWeapon->SetWeaponType(E_WEAPON_TYPE::WEAPON_DUAL_BLADE);
			SubWeapon->AttachMeshToPawn(TEXT("DualBlade_LH"));
			SubWeapon->OwnerCharacterNum = PlayerNum;
		}
		
		break;
	}
}

bool AHT_BaseCharacter::SpawnWeapon_Validate(FItem_Info NewWeaponInfo)
{
	return true;
}

void AHT_BaseCharacter::AttatchWeapon_Implementation(FItem_Info WeaponInfo, const FString& SpawnWeaponName, const FString& SpawnSubWeaponName /*= FString()*/)
{
	if (GetWorld()->IsClient())
	{
		IsWeaponChange = true;

		ChangeWeaponInfo = WeaponInfo;
		ChangeWeaponName = SpawnWeaponName;
		ChangeSubWeaponName = SpawnSubWeaponName;
	}	
}

void AHT_BaseCharacter::BeginAttack_Implementation()
{
	Weapon->Attack();
}

bool AHT_BaseCharacter::BeginAttack_Validate()
{
	return true;
}

void AHT_BaseCharacter::BeginStrongAttack_Implementation()
{
	Weapon->StrongAttack();
}

bool AHT_BaseCharacter::BeginStrongAttack_Validate()
{
	return true;
}

void AHT_BaseCharacter::PointDamage(float Damage)
{
	/*
	
	서버에서 깍아주는 PointDamage;

	*/

	Health -= Damage;

	if (Health <= 0.0f)
	{
		Health = 0.0f;
	}

	ClientPointDamege(Health);

	UE_LOG(LogClass, Warning, TEXT("%s"), TEXT("서버 플레이어 포인트 데미지 함수 호출"));

	/*
	
	피격 몽타주, 죽음 몽타주.
	
	*/
}

void AHT_BaseCharacter::ClientPointDamege_Implementation(float NewHealth)
{
	Health = NewHealth;
	
	/*

	피격 몽타주, 죽음 몽타주.

	*/

	UE_LOG(LogClass, Warning, TEXT("%s"), TEXT("클라이언트 플레이어 포인트 데미지 함수 호출"));
}

void AHT_BaseCharacter::DestroyWeapon_Implementation()
{
	if (Weapon != NULL)
	{
		Weapon->Destroy();
		Weapon = NULL;
	}
	
	if (SubWeapon != NULL)
	{
		SubWeapon->Destroy();
		SubWeapon = NULL;
	}
}

bool AHT_BaseCharacter::DestroyWeapon_Validate()
{
	return true;
}

void AHT_BaseCharacter::AddItem_Implementation(FItem_Info Info)
{
	UHT_GameInstance* GameInstance = Cast<UHT_GameInstance>(GetWorld()->GetGameInstance());

	if (GameInstance != NULL)
	{
		GameInstance->UserInventoryWidget->AddItem(Info);

		TakeItemList.Add(Info);
	}
}

void AHT_BaseCharacter::EquipChange_Server_Implementation(FItem_Info NewEquip)
{
	EquipChange_Client(NewEquip);
}

bool AHT_BaseCharacter::EquipChange_Server_Validate(FItem_Info NewEquip)
{
	return true;
}

void AHT_BaseCharacter::EquipChange_Client_Implementation(FItem_Info NewEquip)
{
	UHT_GameInstance* GameInstance = Cast<UHT_GameInstance>(GetWorld()->GetGameInstance());

	if (GameInstance != NULL)
	{
		switch (NewEquip.Item_Type)
		{
		case E_ITEM_TYPE::ITEM_TYPE_EQUIP_UPPER:

			UpperMesh->SetSkeletalMesh(GameInstance->EquipMeshs[NewEquip.Item_Num - 8]);

			EquipList[0] = NewEquip.Item_Num;

			break;

		case E_ITEM_TYPE::ITEM_TYPE_EQUIP_LOWER:

			LowerMesh->SetSkeletalMesh(GameInstance->EquipMeshs[NewEquip.Item_Num - 8]);

			EquipList[1] = NewEquip.Item_Num;

			break;

		case E_ITEM_TYPE::ITEM_TYPE_EQUIP_FOOT:

			FootMesh->SetSkeletalMesh(GameInstance->EquipMeshs[NewEquip.Item_Num - 8]);

			EquipList[2] = NewEquip.Item_Num;

			break;
		}
	}
}

void AHT_BaseCharacter::DetachEquip_Server_Implementation(E_ITEM_TYPE Equip_Type)
{
	DetachEquip_Client(Equip_Type);
}

bool AHT_BaseCharacter::DetachEquip_Server_Validate(E_ITEM_TYPE Equip_Type)
{
	return true;
}

void AHT_BaseCharacter::DetachEquip_Client_Implementation(E_ITEM_TYPE Equip_Type)
{
	switch (Equip_Type)
	{
	case E_ITEM_TYPE::ITEM_TYPE_EQUIP_UPPER:

		UpperMesh->SetSkeletalMesh(NULL);

		EquipList[0] = 0;

		break;

	case E_ITEM_TYPE::ITEM_TYPE_EQUIP_LOWER:

		LowerMesh->SetSkeletalMesh(NULL);

		EquipList[1] = 0;

		break;

	case E_ITEM_TYPE::ITEM_TYPE_EQUIP_FOOT:

		FootMesh->SetSkeletalMesh(NULL);

		EquipList[2] = 0;

		break;

	case E_ITEM_TYPE::ITEM_TYPE_WEAPON_SCYTHE:

	case E_ITEM_TYPE::ITEM_TYPE_WEAPON_DUAL_BLADE:

		DestroyWeapon();

		break;
	}
}

void AHT_BaseCharacter::ReflashCharacter_Server_Implementation(const FString& PlayerName, const TArray<int>& Equip)
{
	UE_LOG(LogClass, Warning, TEXT("%s"), TEXT("서버에서 동기화 요청 받아들임."));

	ReflashCharacter_Client(PlayerName, Equip);
}

bool AHT_BaseCharacter::ReflashCharacter_Server_Validate(const FString& PlayerName, const TArray<int>& Equip)
{
	return true;
}

void AHT_BaseCharacter::ReflashCharacter_Client_Implementation(const FString& PlayerName, const TArray<int>& Equip)
{
	if (GetWorld()->IsClient())
	{
		UHT_GameInstance* GameInstance = Cast<UHT_GameInstance>(GetWorld()->GetGameInstance());
		AHT_StagePlayerState* StagePlayerStage = Cast<AHT_StagePlayerState>(PlayerState);

		UE_LOG(LogClass, Warning, TEXT("%s"), TEXT("동기화 함수 호출!!"));

		if (GameInstance != NULL)
		{
			UE_LOG(LogClass, Warning, TEXT("%s"), TEXT("게임 인스턴스 있음."));

			if (StagePlayerStage != NULL)
			{
				UE_LOG(LogClass, Warning, TEXT("%s"), TEXT("플레이어 스테이트 있음."));

				if (GameInstance->PlayerNum != StagePlayerStage->ClientPlayerNum)
				{
					if (UserNameWidget != NULL)
					{
						UserNameWidget->UserName = PlayerName;
					}

					for (int i = 0; i < 3; ++i)
					{
						if (Equip[i] == 0)
							continue;

						if (i == 0)
						{
							UpperMesh->SetSkeletalMesh(GameInstance->EquipMeshs[Equip[i] - 8]);
						}
						else if (i == 1)
						{
							LowerMesh->SetSkeletalMesh(GameInstance->EquipMeshs[Equip[i] - 8]);
						}
						else if (i == 2)
						{
							FootMesh->SetSkeletalMesh(GameInstance->EquipMeshs[Equip[i] - 8]);
						}
					}
				}
			}
			/*else
			{
				UE_LOG(LogClass, Warning, TEXT("%s"), TEXT("플레이어 스테이트 없음."));

				if (UserNameWidget != NULL)
				{
					UserNameWidget->UserName = PlayerName;
				}

				for (int i = 0; i < 3; ++i)
				{
					if (Equip[i] == 0)
						continue;

					if (i == 0)
					{
						UpperMesh->SetSkeletalMesh(GameInstance->EquipMeshs[Equip[i] - 8]);
					}
					else if (i == 1)
					{
						LowerMesh->SetSkeletalMesh(GameInstance->EquipMeshs[Equip[i] - 8]);
					}
					else if (i == 2)
					{
						FootMesh->SetSkeletalMesh(GameInstance->EquipMeshs[Equip[i] - 8]);
					}
				}
			}*/
		}
	}
}

void AHT_BaseCharacter::OnMonsterWidget_Implementation(const FString& SpawnName, const FString& MonsterName, float PrevHealth, float CurHealth)
{
	UHT_GameInstance* GameInstance = Cast<UHT_GameInstance>(GetWorld()->GetGameInstance());

	if (GameInstance != NULL)
	{
		GameInstance->MonsterHpWidget->SetVisibility(ESlateVisibility::Visible);

		UTexture2D* MonsterImage = NULL;

		if (MonsterName == FString("Bear"))
		{
			MonsterImage = GameInstance->MonsterImages[0];
		}
		else
		{
			MonsterImage = GameInstance->MonsterImages[1];
		}

		GameInstance->MonsterHpWidget->MonsterTakeDamege(SpawnName, PrevHealth, CurHealth, MonsterName, MonsterImage);
	}
}

// Called when the game starts or when spawned
void AHT_BaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	EquipList.Add(0);
	EquipList.Add(0);
	EquipList.Add(0);

	if (GetWorld()->IsClient())
	{
		UHT_GameInstance* GameInstance = Cast<UHT_GameInstance>(GetWorld()->GetGameInstance());
		AHT_StagePlayerState* StagePlayerStage = Cast<AHT_StagePlayerState>(PlayerState);

		UE_LOG(LogClass, Warning, TEXT("%s"), TEXT("Character Begin Play()"));

		if (GameInstance != NULL && StagePlayerStage != NULL)
		{
			UE_LOG(LogClass, Warning, TEXT("%s"), TEXT("GameInstance가 있고 플레이어 스테이트 변수가 있다."));

			if (GameInstance->PlayerNum == StagePlayerStage->ClientPlayerNum) //소유중인 클라이언트에서 1회 실행.
			{
				GameInstance->PlayerStateWidget->SetOwnerPlayer(this);

				CharacterName = GameInstance->CharacterData[GameInstance->CharacterCurIndex].Name;
				
				IsNetworkCharacter = false;
				IsBeginPlay = true;

				UE_LOG(LogClass, Warning, TEXT("%s"), TEXT("소유중인 클라이언트!"));
				
				if (UserNameWidget != NULL)
				{
					UserNameWidget->UserName = GameInstance->CharacterData[GameInstance->CharacterCurIndex].Name;
				}
			}
		}
		else if (StagePlayerStage == NULL)
		{
			UE_LOG(LogClass, Warning, TEXT("%s"), TEXT("IsNewUser 변수 변경"));

			GameInstance->IsNewUser = true;
		}
	}
}

// Called every frame
void AHT_BaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	/*if (GetWorld()->IsClient())
	{
		UHT_GameInstance* GameInstance = Cast<UHT_GameInstance>(GetWorld()->GetGameInstance());

		UScrollBox* ScrollBox = Cast<UScrollBox>(GameInstance->ChattingWidget->GetWidgetFromName("ChattingLogWidget"));
		ScrollBox->ScrollToEnd();
	}*/ //채팅 기능

	if (GetWorld()->IsClient())
	{
		UHT_GameInstance* GameInstance = Cast<UHT_GameInstance>(GetWorld()->GetGameInstance());

		AHT_StagePlayerState* StagePlayerStage = Cast<AHT_StagePlayerState>(PlayerState);

		if (GameInstance != NULL && StagePlayerStage != NULL)
		{
			if (StagePlayerStage->ClientPlayerNum == GameInstance->PlayerNum) //소유 중인 클라이언트의 Tick()
			{
				if (TakeItemList.Num() != 0 && GameInstance->TakeItemWidget->GetVisibility() == ESlateVisibility::Collapsed)
				{
					GameInstance->TakeItemWidget->SetVisibility(ESlateVisibility::Visible);
					GameInstance->StageWidet->PlayTakeItemAnim(TakeItemList[0]);

					TakeItemList.RemoveAt(0);
				}

				if (GameInstance->IsNewUser)
				{
					AccTime += DeltaTime;

					if (AccTime > 2.0f)
					{
						AccTime = 0.0f;

						UE_LOG(LogClass, Warning, TEXT("%s / %s"), TEXT("서버에 동기화 요청 !"), *CharacterName);

						ReflashCharacter_Server(CharacterName, EquipList);

						GameInstance->IsNewUser = false;
					}
				}
			}
		}
	}
			
	if (IsWeaponChange)
	{
		Weapon = NULL;
		SubWeapon = NULL;

		TArray<AActor*> WeaponList;

		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AHT_BaseWeapon::StaticClass(), WeaponList);

		switch (ChangeWeaponInfo.Item_Type)
		{
		case E_ITEM_TYPE::ITEM_TYPE_WEAPON_SCYTHE:

			for (int i = 0; i < WeaponList.Num(); ++i)
			{
				AHT_BaseWeapon* pWeapon = Cast<AHT_BaseWeapon>(WeaponList[i]);

				if (pWeapon != NULL)
				{
					if (ChangeWeaponName == pWeapon->GetName())
					{
						Weapon = pWeapon;
						Weapon->OwnerCharacter = this;
						Weapon->SetWeaponIndex(ChangeWeaponInfo.Item_Num);
						Weapon->SetWeaponType(E_WEAPON_TYPE::WEAPON_SCYTHE);
						Weapon->AttachMeshToPawn(TEXT("Scythe_RH"));
						Weapon->OwnerCharacterNum = PlayerNum;
						
						IsWeaponChange = false;
						
						ChangeWeaponInfo = FItem_Info();
						ChangeWeaponName = FString();
						ChangeSubWeaponName = FString();

						break;
					}
				}
			}

			break;

		case E_ITEM_TYPE::ITEM_TYPE_WEAPON_DUAL_BLADE:

			for (int i = 0; i < WeaponList.Num(); ++i)
			{
				AHT_BaseWeapon* pWeapon = Cast<AHT_BaseWeapon>(WeaponList[i]);

				if (pWeapon != NULL)
				{
					if (ChangeWeaponName == pWeapon->GetName())
					{
						Weapon = pWeapon;
						Weapon->OwnerCharacter = this;
						Weapon->SetWeaponIndex(ChangeWeaponInfo.Item_Num);
						Weapon->SetWeaponType(E_WEAPON_TYPE::WEAPON_DUAL_BLADE);
						Weapon->AttachMeshToPawn(TEXT("DualBlade_RH"));
						Weapon->OwnerCharacterNum = PlayerNum;

						IsWeaponChange = false;

						ChangeWeaponName = FString();
					}
					else if (ChangeSubWeaponName == pWeapon->GetName())
					{
						SubWeapon = pWeapon;
						SubWeapon->OwnerCharacter = this;
						SubWeapon->SetWeaponIndex(ChangeWeaponInfo.Item_Num);
						SubWeapon->SetWeaponType(E_WEAPON_TYPE::WEAPON_DUAL_BLADE);
						SubWeapon->AttachMeshToPawn(TEXT("DualBlade_LH"));
						SubWeapon->OwnerCharacterNum = PlayerNum;
						
						ChangeSubWeaponName = FString();
					}
				}

				if (ChangeWeaponName == ChangeSubWeaponName)
				{
					ChangeWeaponInfo = FItem_Info();
					IsWeaponChange = false;

					break;
				}
			}

			break;
		}
	}
}

// Called to bind functionality to input
void AHT_BaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AHT_BaseCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AHT_BaseCharacter::MoveRight);

	PlayerInputComponent->BindAxis("CameraRotX", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("CameraRotY", this, &APawn::AddControllerPitchInput);

	if (GetWorld()->IsClient())
	{
		PlayerInputComponent->BindAxis("Zoom", this, &AHT_BaseCharacter::Zoom);
		PlayerInputComponent->BindAction("Inventory", IE_Pressed, this, &AHT_BaseCharacter::OnInventoryWidget);
		//PlayerInputComponent->BindAction("NpcTalk", IE_Pressed, this, &AHT_BaseCharacter::Test);
		//PlayerInputComponent->BindAction("ItemTake", IE_Pressed, this, &AHT_BaseCharacter::Action_ItemTake);
		PlayerInputComponent->BindAction("Enter", IE_Pressed, this, &AHT_BaseCharacter::OnInputTextWidget);
		PlayerInputComponent->BindAction("Space", IE_Pressed, this, &AHT_BaseCharacter::OnTestFunction);
		PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &AHT_BaseCharacter::Attack);
		PlayerInputComponent->BindAction("EquipInventory", IE_Pressed, this, &AHT_BaseCharacter::OnEquipInventoryWidget);
		PlayerInputComponent->BindAction("StrongAttack", IE_Pressed, this, &AHT_BaseCharacter::StrongAttack);
	}
}