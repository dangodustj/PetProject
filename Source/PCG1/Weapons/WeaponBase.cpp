// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponBase.h"


// Sets default values
AWeaponBase::AWeaponBase()
{
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWeaponBase::SetWeaponData(UWeaponData* data)
{
	if (data == nullptr) return;
	WeaponData = data;

	WeaponMesh->SetSkeletalMeshAsset(data->SkeletalMesh);
	WeaponMesh->SetAnimInstanceClass(data->AnimInstanceClass);
}

TArray<FPlayerAbilityData> AWeaponBase::GetAbilities()
{
	if (!IsValid(WeaponData)) return TArray<FPlayerAbilityData>();

	return WeaponData->Abilities;
}

TArray<TSubclassOf<UGameplayEffect>> AWeaponBase::GetEffects()
{
	if (!IsValid(WeaponData)) return TArray<TSubclassOf<UGameplayEffect>>();

	return WeaponData->GrantedEffects;
}

UWeaponData* AWeaponBase::GetWeaponData()
{
	return WeaponData;
}

