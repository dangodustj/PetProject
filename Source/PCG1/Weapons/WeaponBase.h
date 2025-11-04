// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponData.h"
#include "Abilitites/PlayerAbilityData.h"
#include "GameFramework/Actor.h"
#include "WeaponBase.generated.h"

UCLASS()
class PCG1_API AWeaponBase : public AActor
{
	GENERATED_BODY()

protected:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UWeaponData* WeaponData;
	
public:
	// Sets default values for this actor's properties
	AWeaponBase();
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* WeaponMesh;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void SetWeaponData(UWeaponData* data);
	UFUNCTION(BlueprintCallable)
	UWeaponData* GetWeaponData();
	UFUNCTION(BlueprintCallable)
	TArray<FPlayerAbilityData> GetAbilities();
	UFUNCTION(BlueprintCallable)
	TArray<TSubclassOf<UGameplayEffect>> GetEffects();
	
};
