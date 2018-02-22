// Fill out your copyright notice in the Description page of Project Settings.

#include "Hunter.h"
#include "HT_Weapon_DualBlade.h"

AHT_Weapon_DualBlade::AHT_Weapon_DualBlade()
{
	ConstructorHelpers::FObjectFinder<UAnimMontage> AnimMontage1(TEXT("/Game/Female/Animations/Montage/Female_DualBlade_Attack01_Montage"));

	if (AnimMontage1.Object != NULL)
	{
		Attack01_Montage = AnimMontage1.Object;

		UE_LOG(LogClass, Warning, TEXT("%s"), TEXT("몽타주 불러오기 성공"));
	}
	else
	{
		UE_LOG(LogClass, Warning, TEXT("%s"), TEXT("몽타주 불러오기 실패!"));
	}

	ConstructorHelpers::FObjectFinder<UAnimMontage> AnimMontage2(TEXT("/Game/Female/Animations/Montage/Female_DualBlade_Attack02_Montage"));

	if (AnimMontage2.Object != NULL)
	{
		Attack02_Montage = AnimMontage2.Object;

		UE_LOG(LogClass, Warning, TEXT("%s"), TEXT("몽타주 불러오기 성공"));
	}
	else
	{
		UE_LOG(LogClass, Warning, TEXT("%s"), TEXT("몽타주 불러오기 실패!"));
	}

	ConstructorHelpers::FObjectFinder<UAnimMontage> AnimMontage3(TEXT("/Game/Female/Animations/Montage/Female_DualBlade_Attack03_Montage"));

	if (AnimMontage3.Object != NULL)
	{
		Attack03_Montage = AnimMontage3.Object;

		UE_LOG(LogClass, Warning, TEXT("%s"), TEXT("몽타주 불러오기 성공"));
	}
	else
	{
		UE_LOG(LogClass, Warning, TEXT("%s"), TEXT("몽타주 불러오기 실패!"));
	}

	ConstructorHelpers::FObjectFinder<UAnimMontage> AnimMontage4(TEXT("/Game/Female/Animations/Montage/Female_DualBlade_Attack04_Montage"));

	if (AnimMontage4.Object != NULL)
	{
		Attack04_Montage = AnimMontage4.Object;

		UE_LOG(LogClass, Warning, TEXT("%s"), TEXT("몽타주 불러오기 성공"));
	}
	else
	{
		UE_LOG(LogClass, Warning, TEXT("%s"), TEXT("몽타주 불러오기 실패!"));
	}

	ConstructorHelpers::FObjectFinder<UAnimMontage> AnimMontage5(TEXT("/Game/Female/Animations/Montage/Female_DualBlade_StrongAttack01_Montage"));

	if (AnimMontage5.Object != NULL)
	{
		StrongAttack01_Montage = AnimMontage5.Object;

		UE_LOG(LogClass, Warning, TEXT("%s"), TEXT("몽타주 불러오기 성공"));
	}
	else
	{
		UE_LOG(LogClass, Warning, TEXT("%s"), TEXT("몽타주 불러오기 실패!"));
	}

	ConstructorHelpers::FObjectFinder<UAnimMontage> AnimMontage6(TEXT("/Game/Female/Animations/Montage/Female_DualBlade_StrongAttack02_Montage"));

	if (AnimMontage6.Object != NULL)
	{
		StrongAttack02_Montage = AnimMontage6.Object;

		UE_LOG(LogClass, Warning, TEXT("%s"), TEXT("몽타주 불러오기 성공"));
	}
	else
	{
		UE_LOG(LogClass, Warning, TEXT("%s"), TEXT("몽타주 불러오기 실패!"));
	}

	ConstructorHelpers::FObjectFinder<UAnimMontage> AnimMontage7(TEXT("/Game/Female/Animations/Montage/Female_DualBlade_StrongAttack03_Montage"));

	if (AnimMontage7.Object != NULL)
	{
		StrongAttack03_Montage = AnimMontage7.Object;

		UE_LOG(LogClass, Warning, TEXT("%s"), TEXT("몽타주 불러오기 성공"));
	}
	else
	{
		UE_LOG(LogClass, Warning, TEXT("%s"), TEXT("몽타주 불러오기 실패!"));
	}
	
	ConstructorHelpers::FObjectFinder<UAnimMontage> AnimMontage8(TEXT("/Game/Female/Animations/Montage/Female_DualBlade_StrongAttack04_Montage"));

	if (AnimMontage8.Object != NULL)
	{
		StrongAttack04_Montage = AnimMontage8.Object;

		UE_LOG(LogClass, Warning, TEXT("%s"), TEXT("몽타주 불러오기 성공"));
	}
	else
	{
		UE_LOG(LogClass, Warning, TEXT("%s"), TEXT("몽타주 불러오기 실패!"));
	}
}