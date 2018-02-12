// Fill out your copyright notice in the Description page of Project Settings.

#include "Hunter.h"
#include "HT_Weapon_Scythe.h"
#include "HT_BaseMonster.h"

AHT_Weapon_Scythe::AHT_Weapon_Scythe()
	:Super()
{
	//Attack01_Montage

	ConstructorHelpers::FObjectFinder<UAnimMontage> AnimMontage1(TEXT("/Game/Female/Animations/Montage/Female_Scythe_Attack01_Montage"));

	if (AnimMontage1.Object != NULL)
	{
		Attack01_Montage = AnimMontage1.Object;

		UE_LOG(LogClass, Warning, TEXT("%s"), TEXT("몽타주 불러오기 성공"));
	}
	else
	{
		UE_LOG(LogClass, Warning, TEXT("%s"), TEXT("몽타주 불러오기 실패!"));
	}

	ConstructorHelpers::FObjectFinder<UAnimMontage> AnimMontage2(TEXT("/Game/Female/Animations/Montage/Female_Scythe_Attack02_Montage"));

	if (AnimMontage2.Object != NULL)
	{
		Attack02_Montage = AnimMontage2.Object;

		UE_LOG(LogClass, Warning, TEXT("%s"), TEXT("몽타주 불러오기 성공"));
	}
	else
	{
		UE_LOG(LogClass, Warning, TEXT("%s"), TEXT("몽타주 불러오기 실패!"));
	}

	ConstructorHelpers::FObjectFinder<UAnimMontage> AnimMontage3(TEXT("/Game/Female/Animations/Montage/Female_Scythe_Attack03_Montage"));

	if (AnimMontage3.Object != NULL)
	{
		Attack03_Montage = AnimMontage3.Object;

		UE_LOG(LogClass, Warning, TEXT("%s"), TEXT("몽타주 불러오기 성공"));
	}
	else
	{
		UE_LOG(LogClass, Warning, TEXT("%s"), TEXT("몽타주 불러오기 실패!"));
	}

	ConstructorHelpers::FObjectFinder<UAnimMontage> AnimMontage4(TEXT("/Game/Female/Animations/Montage/Female_Scythe_Attack04_Montage"));

	if (AnimMontage4.Object != NULL)
	{
		Attack04_Montage = AnimMontage4.Object;

		UE_LOG(LogClass, Warning, TEXT("%s"), TEXT("몽타주 불러오기 성공"));
	}
	else
	{
		UE_LOG(LogClass, Warning, TEXT("%s"), TEXT("몽타주 불러오기 실패!"));
	}
}