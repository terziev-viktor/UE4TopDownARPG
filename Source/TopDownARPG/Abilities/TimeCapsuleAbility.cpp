// Fill out your copyright notice in the Description page of Project Settings.


#include "TimeCapsuleAbility.h"
#include "TopDownARPG.h"
#include "Engine/World.h"


void UTimeCapsuleAbility::Activate(AActor* Source)
{
	Super::Activate(Source);

	UWorld* World = GetWorld();
	if (IsValid(World) == false)
	{
		UE_LOG(LogTopDownARPG, Error, TEXT("UTimeCapsuleAbility::Activate IsValid(World) == false"));
	}

	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Owner = Source;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	FVector SpawnLocation = Source->GetActorLocation() + Source->GetActorForwardVector();

	AActor* Projectile = World->SpawnActor<ATimeCapsule>(ATimeCapsule::StaticClass(), SpawnLocation, Source->GetActorRotation(), SpawnParameters);
	if (IsValid(Projectile) == false)
	{
		UE_LOG(LogTopDownARPG, Error, TEXT("UTimeCapsuleAbility::Activate IsValid(Projectile) == false"));
		return;
	}
}