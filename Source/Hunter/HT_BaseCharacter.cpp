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

	UserNameWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("UserNameWidget"));
	UserNameWidget->SetupAttachment(RootComponent);

	
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
			GetWorld()->GetFirstPlayerController()->bShowMouseCursor = false;
			GetWorld()->GetFirstPlayerController()->bEnableClickEvents = false;
		}
		else
		{
			GameInstance->UserInventoryWidget->SetVisibility(ESlateVisibility::Visible);
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

void AHT_BaseCharacter::Test()
{
	UHT_GameInstance* GameInstance = Cast<UHT_GameInstance>(GetWorld()->GetGameInstance());

	FRotator SpawnRotation(0.f, 0.f, 0.f);
	FVector SpawnLocal(0.f, 0.f, 100.0f);

	AHT_DropItem* pItem = GetWorld()->SpawnActor<AHT_DropItem>(GameInstance->DropItemClass, SpawnLocal, SpawnRotation);

	pItem->AddItem(0);
	pItem->AddItem(1);
	pItem->AddItem(2);
}

void AHT_BaseCharacter::Action_ItemTake()
{
	UHT_GameInstance* GameInstance = Cast<UHT_GameInstance>(GetWorld()->GetGameInstance());

	if (GameInstance != NULL)
	{
		if (GameInstance->DropItemWidget->GetVisibility() == ESlateVisibility::Visible)
		{
			GameInstance->DropItemWidget->TakeAllDropItem();
		}
		else
		{
			FVector UserPos = GetActorLocation();

			float BastDist = 99999.0f;

			int Index = 0;

			for (int i = 0; i < DropItemArr.Num(); ++i)
			{
				float Dist = (DropItemArr[i]->GetActorLocation() - UserPos).SizeSquared();

				if (Dist < BastDist)
				{
					BastDist = Dist;
					Index = i;
				}
			}

			if (Index < DropItemArr.Num())
			{
				GameInstance->DropItemWidget->SetVisibility(ESlateVisibility::Visible);
				GameInstance->DropItemWidget->SetDropItem(DropItemArr[Index]);
			}
		}
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
	UHT_GameInstance* GameInstance = Cast<UHT_GameInstance>(GetWorld()->GetGameInstance());

	if (GameInstance == NULL)
		return;

	switch (NewEquip.Item_Type)
	{
	case E_ITEM_TYPE::ITEM_TYPE_EQUIP_UPPER:

		UpperMesh->SetSkeletalMesh(GameInstance->EquipMeshs[NewEquip.Item_Num - 8]);
		
		break;

	case E_ITEM_TYPE::ITEM_TYPE_EQUIP_LOWER:

		LowerMesh->SetSkeletalMesh(GameInstance->EquipMeshs[NewEquip.Item_Num - 11]);

		break;

	case E_ITEM_TYPE::ITEM_TYPE_EQUIP_FOOT:

		FootMesh->SetSkeletalMesh(GameInstance->EquipMeshs[NewEquip.Item_Num - 14]);

		break;
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
		MoveForward(0.01f);
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
		
		break;
	}
}

bool AHT_BaseCharacter::SpawnWeapon_Validate(FItem_Info NewWeaponInfo)
{
	return true;
}

void AHT_BaseCharacter::AttatchWeapon_Implementation(FItem_Info WeaponInfo, const FString& SpawnWeaponName, const FString& SpawnSubWeaponName /*= FString()*/)
{
	IsWeaponChange = true;

	ChangeWeaponInfo = WeaponInfo;
	ChangeWeaponName = SpawnWeaponName;
	ChangeSubWeaponName = SpawnSubWeaponName;
}

void AHT_BaseCharacter::BeginAttack_Implementation()
{
	Weapon->Attack();
}

bool AHT_BaseCharacter::BeginAttack_Validate()
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

		UE_LOG(LogClass, Warning, TEXT("%s"), TEXT("무기를 지웠다!"));
	}
	else
	{
		UE_LOG(LogClass, Warning, TEXT("%s"), TEXT("무기를 못 지웠다!"));
	}
}

bool AHT_BaseCharacter::DestroyWeapon_Validate()
{
	return true;
}

// Called when the game starts or when spawned
void AHT_BaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	UHT_UserNameWidget* Widget = Cast<UHT_UserNameWidget>(UserNameWidget->GetUserWidgetObject());

	if (Widget != NULL)
	{
		UHT_GameInstance* GameInstance = Cast<UHT_GameInstance>(GetWorld()->GetGameInstance());
		Widget->UserName = TEXT("진서연")/*GameInstance->UserInfo.ID*/;
	}

	if (GetWorld()->IsClient()) //소유중인 클라이언트에서만 실행.
	{
		UHT_GameInstance* GameInstance = Cast<UHT_GameInstance>(GetWorld()->GetGameInstance());
		
		if (GameInstance != NULL)
		{
			AHT_StagePlayerState* StagePlayerStage = Cast<AHT_StagePlayerState>(PlayerState);

			if (StagePlayerStage != NULL)
			{
				if (StagePlayerStage->ClientPlayerNum == GameInstance->PlayerNum)
				{
					GameInstance->PlayerStateWidget->SetOwnerPlayer(this);

					UE_LOG(LogClass, Warning, TEXT("%s"), TEXT("UI 설정 !!"));

				}
			}			
		}
	}
}
//
//void AHT_BaseCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
//{
//	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
//}

// Called every frame
void AHT_BaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GetWorld()->IsClient())
	{
		UHT_GameInstance* GameInstance = Cast<UHT_GameInstance>(GetWorld()->GetGameInstance());

		UScrollBox* ScrollBox = Cast<UScrollBox>(GameInstance->ChattingWidget->GetWidgetFromName("ChattingLogWidget"));
		ScrollBox->ScrollToEnd();
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
		PlayerInputComponent->BindAction("NpcTalk", IE_Pressed, this, &AHT_BaseCharacter::Test);
		PlayerInputComponent->BindAction("ItemTake", IE_Pressed, this, &AHT_BaseCharacter::Action_ItemTake);
		PlayerInputComponent->BindAction("Enter", IE_Pressed, this, &AHT_BaseCharacter::OnInputTextWidget);
		PlayerInputComponent->BindAction("Space", IE_Pressed, this, &AHT_BaseCharacter::OnTestFunction);
		PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &AHT_BaseCharacter::Attack);
	}
}