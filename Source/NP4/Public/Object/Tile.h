// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Tile.generated.h"

UCLASS()
class NP4_API ATile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATile();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

public:
	

	//UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Tile)
	//TSubobjectPtr<USphereComponent*> m_BaseCollisionComponenet;

	FORCEINLINE class UStaticMeshComponent* GetMesh() const { return TileMesh; }
	UFUNCTION(BlueprintPure, Category = "Tile")
	bool GetBuilding();

	UFUNCTION(BlueprintCallable, Category = "Tile")
		void SetBuilding(bool NewBuildState);

protected:
	// 건설 여부
	bool m_bIsBuild;

private:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Tile", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* TileMesh;


	
	
};
