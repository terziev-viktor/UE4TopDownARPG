// Fill out your copyright notice in the Description page of Project Settings.


#include "TimeCapsule.h"
#include "TopDownARPGCharacter.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "TopDownARPG.h"
#include "Engine/World.h"

// Sets default values
ATimeCapsule::ATimeCapsule()
{
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->InitSphereRadius(this->Radius);
	SphereComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	SphereComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	RootComponent = SphereComponent;

	SphereComponent->OnComponentBeginOverlap.AddUniqueDynamic(this, &ATimeCapsule::OnBeginOverlap);
	SphereComponent->OnComponentEndOverlap.AddUniqueDynamic(this, &ATimeCapsule::OnEndOverlap);
	
	UWorld* World = GetWorld();
	if (IsValid(World) == false)
	{
		UE_LOG(LogTopDownARPG, Error, TEXT("UAbility::Activate IsValid(World) == false"));
		return;
	}

	TimerManager = &World->GetTimerManager();
	TimerManager->SetTimer(CooldownTimerHandle, this, &ATimeCapsule::OnTimerExpired, TimeOfEffect, true, TimeOfEffectDilation);
}


void ATimeCapsule::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//if (Other && OtherComp && Other != this->GetOwner())
	{
		Other->CustomTimeDilation = this->SlowTo;
	}
}

void ATimeCapsule::OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//if (Other && OtherComp && Other != this->GetOwner())
	{
		Other->CustomTimeDilation = 1.0f;
	}
}

void ATimeCapsule::OnTimerExpired()
{
	if (IsValid(this->OnDestroyParticle))
	{
		this->OnDestroyParticle->Activate();
	}
	if (!this->Destroy())
	{
		UE_LOG(LogTopDownARPG, Error, TEXT("UBoltAbility::Activate IsValid(Projectile) == false"));
	}
}
