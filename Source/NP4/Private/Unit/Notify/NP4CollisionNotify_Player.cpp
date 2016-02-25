// Fill out your copyright notice in the Description page of Project Settings.

#include "NP4.h"
#include "NP4CollisionNotify_Player.h"
#include "NP4CharacterBase.h"

UNP4CollisionNotify_Player::UNP4CollisionNotify_Player()
{
	m_sSocketName = "RightHand";
}

void UNP4CollisionNotify_Player::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

}
