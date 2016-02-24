// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "ItemBase.generated.h"

UENUM(BlueprintType)		//"BlueprintType" is essential to include
enum class eItemType : uint8
{
	eNone = 0,
	eWeapon = 1,
	eArmor = 2,
	ePortion = 3
};

UCLASS()
class NP4_API AItemBase : public AActor
{
	GENERATED_BODY()
		
protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	int32 m_iItemID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	UTexture2D* m_tItemImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	UTexture2D* m_tItemImage_Using;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	eItemType m_eItemType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	FName m_sItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	FText m_sItemDescription;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	float m_fItemAttackValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	bool m_bItemState_IsUsing;

public:	
	// Sets default values for this actor's properties
	AItemBase();
	
public:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;
	
};
