// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Ability.h"
#include "Projectiles/TimeCapsule.h"

#include "TimeCapsuleAbility.generated.h"
/**
 * 
 */
UCLASS()
class TOPDOWNARPG_API UTimeCapsuleAbility : public UAbility
{
	GENERATED_BODY()
	
public:
	virtual void Activate(AActor * Source) override;
private:
};
