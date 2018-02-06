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

	PlayerState = E_PLAYER_STATE::PLAYER_STATE_IDLE;
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
		Weapon->Attack();

		UE_LOG(LogClass, Warning, TEXT("%s"), TEXT("°ø°Ý!!!"));
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

				UE_LOG(LogClass, Warning, TEXT("%s"), TEXT("Æ÷Ä¿½º ¼ÂÆÃ"));
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

	//IsWeaponChange = true;
}

FName AHT_BaseCharacter::GetWeaponAttachPointName() const
{
	return WeaponAttachPointName;
}

void AHT_BaseCharacter::WeaponChange(FItem_Info NewWeaponInfo)
{
	if (Weapon != NULL)
	{
		Weapon->Destroy();
		Weapon = NULL;
	}

	FRotator SpawnRotation(0.0f, 0.0f, 0.0f);
	FVector SpawnLocal(0.0f, 0.0f, 0.0f);

	switch (NewWeaponInfo.Item_Type)
	{
		case E_ITEM_TYPE::ITEM_TYPE_WEAPON_SCYTHE:

			Weapon = GetWorld()->SpawnActor<AHT_BaseWeapon>(AHT_Weapon_Scythe::StaticClass(), SpawnLocal, SpawnRotation);
			Weapon->OwnerCharacter = this;
			Weapon->SetWeaponIndex(NewWeaponInfo.Item_Num);
			Weapon->SetWeaponType(E_WEAPON_TYPE::WEAPON_SCYTHE);
			Weapon->AttachMeshToPawn(TEXT("Scythe_RH"));
			
			UE_LOG(LogClass, Warning, TEXT("%s"), TEXT("³´ ÀåÂø"));

			break;

		case E_ITEM_TYPE::ITEM_TYPE_WEAPON_DUAL_BLADE:

			Weapon = GetWorld()->SpawnActor<AHT_BaseWeapon>(AHT_Weapon_DualBlade::StaticClass(), SpawnLocal, SpawnRotation);
			Weapon->OwnerCharacter = this;
			Weapon->SetWeaponIndex(NewWeaponInfo.Item_Num);
			Weapon->SetWeaponType(E_WEAPON_TYPE::WEAPON_DUAL_BLADE);
			Weapon->AttachMeshToPawn(TEXT("DualBlade_RH"));

			UE_LOG(LogClass, Warning, TEXT("%s"), TEXT("µà¾ó ºí·¹ÀÌµå ÀåÂø"));
			
			break;
	}	
}

void AHT_BaseCharacter::SetPlayerState(E_PLAYER_STATE NewPlayerState)
{
	PlayerState = NewPlayerState;
}

E_PLAYER_STATE AHT_BaseCharacter::GetPlayerState()
{
	return PlayerState;
}

void AHT_BaseCharacter::OnOverlapBegin(class UPrimitiveComponent* OverlappingComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(AHT_DropItem::StaticClass()))
	{
		DropItemArr.Add((AHT_DropItem*)OtherActor);
	}
	else if (OtherActor->IsA(AHT_BaseNPC::StaticClass()))
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

// Called when the game starts or when spawned
void AHT_BaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	UHT_UserNameWidget* Widget = Cast<UHT_UserNameWidget>(UserNameWidget->GetUserWidgetObject());

	if (Widget != NULL)
	{
		UHT_GameInstance* GameInstance = Cast<UHT_GameInstance>(GetWorld()->GetGameInstance());
		Widget->UserName = GameInstance->UserInfo.ID;
	}
}

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
		PlayerInputComponent->BindAction("Inventory", IE_Pressed, this, &AHT_BaseCharacter::OnInventoryWidget);
		PlayerInputComponent->BindAction("NpcTalk", IE_Pressed, this, &AHT_BaseCharacter::Test);
		PlayerInputComponent->BindAction("ItemTake", IE_Pressed, this, &AHT_BaseCharacter::Action_ItemTake);
		PlayerInputComponent->BindAction("Enter", IE_Pressed, this, &AHT_BaseCharacter::OnInputTextWidget);
		PlayerInputComponent->BindAction("Space", IE_Pressed, this, &AHT_BaseCharacter::OnTestFunction);
		PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &AHT_BaseCharacter::Attack);
	}
}