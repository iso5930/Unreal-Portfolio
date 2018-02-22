// Fill out your copyright notice in the Description page of Project Settings.

#include "Hunter.h"
#include "HT_GameInstance.h"
#include "Engine.h"
#include "Runtime/Networking/Public/Networking.h"
#include "Runtime/Sockets/Public/Sockets.h"
#include "Runtime/Sockets/Public/SocketSubsystem.h"
#include "Runtime/Core/Public/HAL/RunnableThread.h"
#include "HT_LoginThread.h"

UHT_GameInstance::UHT_GameInstance()
{
	TArray<TCHAR*> WeaponPaths;

	WeaponPaths.Add(TEXT("/Game/Weapon/Scythe/Mesh/Scythe"));
	WeaponPaths.Add(TEXT("/Game/Weapon/Dual/Mesh/Dual"));

	for (int32 i = 0; i < WeaponPaths.Num(); ++i)
	{
		ConstructorHelpers::FObjectFinder<USkeletalMesh> WeaponMesh(WeaponPaths[i]);

		if (WeaponMesh.Object != NULL)
		{
			WeaponMeshs.Add(WeaponMesh.Object);
		}
		else
		{
			UE_LOG(LogClass, Warning, TEXT("%d %s %s"), i, TEXT("Weapon Mesh Loading Error!"), WeaponPaths[i]);
		}
	}

	UE_LOG(LogClass, Warning, TEXT("%s"), TEXT("게임 인스턴스 생성"));

	TArray<TCHAR*> EquipPaths;

	EquipPaths.Add(TEXT("/Game/Female/Clothing/Upper/Mesh/Female_Hoodie_Upper"));
	EquipPaths.Add(TEXT("/Game/Female/Clothing/Upper/Mesh/Female_Gangster_Upper"));
	EquipPaths.Add(TEXT("/Game/Female/Clothing/Upper/Mesh/Female_Ninja_Upper"));

	EquipPaths.Add(TEXT("/Game/Female/Clothing/Lower/Mesh/Female_Hoodie_Lower"));
	EquipPaths.Add(TEXT("/Game/Female/Clothing/Lower/Mesh/Female_Gangster_Lower"));
	EquipPaths.Add(TEXT("/Game/Female/Clothing/Lower/Mesh/Female_Ninja_Lower"));

	EquipPaths.Add(TEXT("/Game/Female/Clothing/Foot/Mesh/Female_Hoodie_Foot"));
	EquipPaths.Add(TEXT("/Game/Female/Clothing/Foot/Mesh/Female_Gangster_Foot"));
	EquipPaths.Add(TEXT("/Game/Female/Clothing/Foot/Mesh/Female_Ninja_Foot"));

	for (int32 i = 0; i < EquipPaths.Num(); ++i)
	{
		ConstructorHelpers::FObjectFinder<USkeletalMesh> EquipMesh(EquipPaths[i]);

		if (EquipMesh.Object != NULL)
		{
			EquipMeshs.Add(EquipMesh.Object);
		}
		else
		{
			UE_LOG(LogClass, Warning, TEXT("%d %s %s"), i, TEXT("Weapon Mesh Loading Error!"), EquipPaths[i]);
		}
	}

	TArray<TCHAR*> MonsterImagePaths;

	MonsterImagePaths.Add(TEXT("/Game/Image/Bear"));
	MonsterImagePaths.Add(TEXT("/Game/Image/Troll"));

	for (int32 i = 0; i < MonsterImagePaths.Num(); ++i)
	{
		ConstructorHelpers::FObjectFinder<UTexture2D> MonsterImage(MonsterImagePaths[i]);

		if (MonsterImage.Object != NULL)
		{
			MonsterImages.Add(MonsterImage.Object);
		}
		else
		{
			UE_LOG(LogClass, Warning, TEXT("%d %s %s"), i, TEXT("Monster Image Loading Error!"), MonsterImagePaths[i]);
		}
	}

	FItem_Info ItemInfo;

	ConstructorHelpers::FObjectFinder<UTexture2D> Item00(TEXT("/Game/Image/000"));

	if (Item00.Object != NULL)
	{
		ItemInfo.Item_Image = Item00.Object;
	}

	ItemInfo.Item_Num = 0;
	ItemInfo.Item_Name = FString(TEXT("초보자용 HP 포션"));
	ItemInfo.Item_Cnt = 1;
	ItemInfo.Item_MaxCnt = 999;
	ItemInfo.Item_Type = E_ITEM_TYPE::ITEM_TYPE_POTION;

	Item_DataBase.Add(ItemInfo);

	ConstructorHelpers::FObjectFinder<UTexture2D> Item01(TEXT("/Game/Image/001"));

	if (Item01.Object != NULL)
	{
		ItemInfo.Item_Image = Item01.Object;
	}

	ItemInfo.Item_Num = 1;
	ItemInfo.Item_Name = FString(TEXT("초보자용 MP 포션"));
	ItemInfo.Item_Cnt = 1;
	ItemInfo.Item_MaxCnt = 999;
	ItemInfo.Item_Type = E_ITEM_TYPE::ITEM_TYPE_POTION;

	Item_DataBase.Add(ItemInfo);

	ConstructorHelpers::FObjectFinder<UTexture2D> Item02(TEXT("/Game/Image/002"));

	if (Item02.Object != NULL)
	{
		ItemInfo.Item_Image = Item02.Object;
	}

	ItemInfo.Item_Num = 2;
	ItemInfo.Item_Name = FString(TEXT("중급자용 HP 포션"));
	ItemInfo.Item_Cnt = 1;
	ItemInfo.Item_MaxCnt = 999;
	ItemInfo.Item_Type = E_ITEM_TYPE::ITEM_TYPE_POTION;

	Item_DataBase.Add(ItemInfo);

	ConstructorHelpers::FObjectFinder<UTexture2D> Item03(TEXT("/Game/Image/003"));

	if (Item03.Object != NULL)
	{
		ItemInfo.Item_Image = Item03.Object;
	}

	ItemInfo.Item_Num = 3;
	ItemInfo.Item_Name = FString(TEXT("중급자용 MP 포션"));
	ItemInfo.Item_Cnt = 1;
	ItemInfo.Item_MaxCnt = 999;
	ItemInfo.Item_Type = E_ITEM_TYPE::ITEM_TYPE_POTION;

	Item_DataBase.Add(ItemInfo);

	ConstructorHelpers::FObjectFinder<UTexture2D> Item04(TEXT("/Game/Image/004"));

	if (Item04.Object != NULL)
	{
		ItemInfo.Item_Image = Item04.Object;
	}

	ItemInfo.Item_Num = 4;
	ItemInfo.Item_Name = FString(TEXT("숙련자용 HP 포션"));
	ItemInfo.Item_Cnt = 1;
	ItemInfo.Item_MaxCnt = 999;
	ItemInfo.Item_Type = E_ITEM_TYPE::ITEM_TYPE_POTION;

	Item_DataBase.Add(ItemInfo);

	ConstructorHelpers::FObjectFinder<UTexture2D> Item05(TEXT("/Game/Image/005"));

	if (Item05.Object != NULL)
	{
		ItemInfo.Item_Image = Item05.Object;
	}

	ItemInfo.Item_Num = 5;
	ItemInfo.Item_Name = FString(TEXT("숙련자용 MP 포션"));
	ItemInfo.Item_Cnt = 1;
	ItemInfo.Item_MaxCnt = 999;
	ItemInfo.Item_Type = E_ITEM_TYPE::ITEM_TYPE_POTION;

	Item_DataBase.Add(ItemInfo);

	ConstructorHelpers::FObjectFinder<UTexture2D> Item06(TEXT("/Game/Image/eq_scythe"));

	if (Item06.Object != NULL)
	{
		ItemInfo.Item_Image = Item06.Object;
	}

	ItemInfo.Item_Num = 6;
	ItemInfo.Item_Name = FString(TEXT("초보자용 사이드"));
	ItemInfo.Item_Cnt = 1;
	ItemInfo.Item_MaxCnt = 1;
	ItemInfo.Item_Type = E_ITEM_TYPE::ITEM_TYPE_WEAPON_SCYTHE;

	Item_DataBase.Add(ItemInfo);

	ConstructorHelpers::FObjectFinder<UTexture2D> Item07(TEXT("/Game/Image/eq_dualsword_aidan"));

	if (Item07.Object != NULL)
	{
		ItemInfo.Item_Image = Item07.Object;
	}

	ItemInfo.Item_Num = 7;
	ItemInfo.Item_Name = FString(TEXT("초보자용 듀얼 블레이드"));
	ItemInfo.Item_Cnt = 1;
	ItemInfo.Item_MaxCnt = 1;
	ItemInfo.Item_Type = E_ITEM_TYPE::ITEM_TYPE_WEAPON_DUAL_BLADE;

	Item_DataBase.Add(ItemInfo);
	
	ConstructorHelpers::FObjectFinder<UTexture2D> Item08(TEXT("/Game/Image/eq_hoodie_jpn_female_upper"));

	if (Item08.Object != NULL)
	{
		ItemInfo.Item_Image = Item08.Object;
	}

	ItemInfo.Item_Num = 8;
	ItemInfo.Item_Name = FString(TEXT("후디 상의"));
	ItemInfo.Item_Cnt = 1;
	ItemInfo.Item_MaxCnt = 1;
	ItemInfo.Item_Type = E_ITEM_TYPE::ITEM_TYPE_EQUIP_UPPER;

	Item_DataBase.Add(ItemInfo);

	ConstructorHelpers::FObjectFinder<UTexture2D> Item09(TEXT("/Game/Image/eq_gangster_female_upper"));

	if (Item09.Object != NULL)
	{
		ItemInfo.Item_Image = Item09.Object;
	}

	ItemInfo.Item_Num = 9;
	ItemInfo.Item_Name = FString(TEXT("갱스터 상의"));
	ItemInfo.Item_Cnt = 1;
	ItemInfo.Item_MaxCnt = 1;
	ItemInfo.Item_Type = E_ITEM_TYPE::ITEM_TYPE_EQUIP_UPPER;

	Item_DataBase.Add(ItemInfo);

	ConstructorHelpers::FObjectFinder<UTexture2D> Item10(TEXT("/Game/Image/eq_ninja_female_upper"));

	if (Item10.Object != NULL)
	{
		ItemInfo.Item_Image = Item10.Object;
	}

	ItemInfo.Item_Num = 10;
	ItemInfo.Item_Name = FString(TEXT("닌자 상의"));
	ItemInfo.Item_Cnt = 1;
	ItemInfo.Item_MaxCnt = 1;
	ItemInfo.Item_Type = E_ITEM_TYPE::ITEM_TYPE_EQUIP_UPPER;


	Item_DataBase.Add(ItemInfo);

	ConstructorHelpers::FObjectFinder<UTexture2D> Item11(TEXT("/Game/Image/eq_hoodie_jpn_female_Lower"));

	if (Item11.Object != NULL)
	{
		ItemInfo.Item_Image = Item11.Object;
	}

	ItemInfo.Item_Num = 11;
	ItemInfo.Item_Name = FString(TEXT("후디 하의"));
	ItemInfo.Item_Cnt = 1;
	ItemInfo.Item_MaxCnt = 1;
	ItemInfo.Item_Type = E_ITEM_TYPE::ITEM_TYPE_EQUIP_LOWER;

	Item_DataBase.Add(ItemInfo);

	ConstructorHelpers::FObjectFinder<UTexture2D> Item12(TEXT("/Game/Image/eq_gangster_female_Lower"));

	if (Item12.Object != NULL)
	{
		ItemInfo.Item_Image = Item12.Object;
	}

	ItemInfo.Item_Num = 12;
	ItemInfo.Item_Name = FString(TEXT("갱스터 하의"));
	ItemInfo.Item_Cnt = 1;
	ItemInfo.Item_MaxCnt = 1;
	ItemInfo.Item_Type = E_ITEM_TYPE::ITEM_TYPE_EQUIP_LOWER;

	Item_DataBase.Add(ItemInfo);

	ConstructorHelpers::FObjectFinder<UTexture2D> Item13(TEXT("/Game/Image/eq_ninja_female_Lower"));

	if (Item13.Object != NULL)
	{
		ItemInfo.Item_Image = Item13.Object;
	}

	ItemInfo.Item_Num = 13;
	ItemInfo.Item_Name = FString(TEXT("닌자 하의"));
	ItemInfo.Item_Cnt = 1;
	ItemInfo.Item_MaxCnt = 1;
	ItemInfo.Item_Type = E_ITEM_TYPE::ITEM_TYPE_EQUIP_LOWER;

	Item_DataBase.Add(ItemInfo);



	ConstructorHelpers::FObjectFinder<UTexture2D> Item14(TEXT("/Game/Image/eq_hoodie_jpn_female_Foot"));

	if (Item14.Object != NULL)
	{
		ItemInfo.Item_Image = Item14.Object;
	}

	ItemInfo.Item_Num = 14;
	ItemInfo.Item_Name = FString(TEXT("후디 신발"));
	ItemInfo.Item_Cnt = 1;
	ItemInfo.Item_MaxCnt = 1;
	ItemInfo.Item_Type = E_ITEM_TYPE::ITEM_TYPE_EQUIP_FOOT;

	Item_DataBase.Add(ItemInfo);

	ConstructorHelpers::FObjectFinder<UTexture2D> Item15(TEXT("/Game/Image/eq_gangster_female_Foot"));

	if (Item15.Object != NULL)
	{
		ItemInfo.Item_Image = Item15.Object;
	}

	ItemInfo.Item_Num = 15;
	ItemInfo.Item_Name = FString(TEXT("갱스터 신발"));
	ItemInfo.Item_Cnt = 1;
	ItemInfo.Item_MaxCnt = 1;
	ItemInfo.Item_Type = E_ITEM_TYPE::ITEM_TYPE_EQUIP_FOOT;

	Item_DataBase.Add(ItemInfo);

	ConstructorHelpers::FObjectFinder<UTexture2D> Item16(TEXT("/Game/Image/eq_ninja_female_Foot"));

	if (Item16.Object != NULL)
	{
		ItemInfo.Item_Image = Item16.Object;
	}

	ItemInfo.Item_Num = 16;
	ItemInfo.Item_Name = FString(TEXT("닌자 신발"));
	ItemInfo.Item_Cnt = 1;
	ItemInfo.Item_MaxCnt = 1;
	ItemInfo.Item_Type = E_ITEM_TYPE::ITEM_TYPE_EQUIP_FOOT;

	Item_DataBase.Add(ItemInfo);
}

void UHT_GameInstance::SetNetwork(bool IsCheck)
{
	IsNetwork = IsCheck;

	if (!IsNetwork)
	{
		FString strID = TEXT("Local Player");
		FString strPW = TEXT("");
		//lstrcpy(UserInfo.ID, *strID);
		//lstrcpy(UserInfo.PW, *strPW);
	}
}

bool UHT_GameInstance::GetNetwork()
{
	return IsNetwork;
}

void UHT_GameInstance::Init_Network(FString ID, FString PW)
{
	MemberInfo Info;

	memset(&Info, 0, sizeof(Info));

	for (int i = 0; i < ID.Len(); ++i)
	{
		Info.ID[i] = (*ID)[i];
	}

	for (int i = 0; i < PW.Len(); ++i)
	{
		Info.PW[i] = (*PW)[i];
	}

	UserInfo = Info;

	FHT_LoginThread::GetInstance()->JoyInit(Info, this);
}

void UHT_GameInstance::FinishDestroy()
{
	Super::FinishDestroy();

	if (ChattingSocket != NULL)
	{
		ChattingSocket->Close();
		ChattingSocket = NULL;
	}
}