// Fill out your copyright notice in the Description page of Project Settings.

#include "Hunter.h"
#include "HT_Weapon_DualBlade.h"

AHT_Weapon_DualBlade::AHT_Weapon_DualBlade()
{
	ConstructorHelpers::FObjectFinder<UAnimMontage> AnimMontage1(TEXT("/Game/Female/Animations/Montage/Female_Double_Attack01_Montage"));

	if (AnimMontage1.Object != NULL)
	{
		Attack01_Montage = AnimMontage1.Object;

		UE_LOG(LogClass, Warning, TEXT("%s"), TEXT("��Ÿ�� �ҷ����� ����"));
	}
	else
	{
		UE_LOG(LogClass, Warning, TEXT("%s"), TEXT("��Ÿ�� �ҷ����� ����!"));
	}

	ConstructorHelpers::FObjectFinder<UAnimMontage> AnimMontage2(TEXT("/Game/Female/Animations/Montage/Female_Double_Attack02_Montage"));

	if (AnimMontage2.Object != NULL)
	{
		Attack02_Montage = AnimMontage2.Object;

		UE_LOG(LogClass, Warning, TEXT("%s"), TEXT("��Ÿ�� �ҷ����� ����"));
	}
	else
	{
		UE_LOG(LogClass, Warning, TEXT("%s"), TEXT("��Ÿ�� �ҷ����� ����!"));
	}

	ConstructorHelpers::FObjectFinder<UAnimMontage> AnimMontage3(TEXT("/Game/Female/Animations/Montage/Female_Double_Attack03_Montage"));

	if (AnimMontage3.Object != NULL)
	{
		Attack03_Montage = AnimMontage3.Object;

		UE_LOG(LogClass, Warning, TEXT("%s"), TEXT("��Ÿ�� �ҷ����� ����"));
	}
	else
	{
		UE_LOG(LogClass, Warning, TEXT("%s"), TEXT("��Ÿ�� �ҷ����� ����!"));
	}

	ConstructorHelpers::FObjectFinder<UAnimMontage> AnimMontage4(TEXT("/Game/Female/Animations/Montage/Female_Double_Attack04_Montage"));

	if (AnimMontage4.Object != NULL)
	{
		Attack04_Montage = AnimMontage4.Object;

		UE_LOG(LogClass, Warning, TEXT("%s"), TEXT("��Ÿ�� �ҷ����� ����"));
	}
	else
	{
		UE_LOG(LogClass, Warning, TEXT("%s"), TEXT("��Ÿ�� �ҷ����� ����!"));
	}
}

void AHT_Weapon_DualBlade::Attack()
{
	Super::Attack();
}