// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Runtime/Engine/Classes/Components/SphereComponent.h"
#include "TimeCapsule.generated.h"

UCLASS()
class TOPDOWNARPG_API ATimeCapsule : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATimeCapsule();

	float SlowTo = 0.2f;

	unsigned short Radius = 160;

protected:


	UPROPERTY(VisibleAnywhere, Category = Gameplay)
	USphereComponent* SphereComponent;

	UPROPERTY(VisibleAnywhere, Category = Visual)
	class UParticleSystemComponent* OnDestroyParticle;

	UFUNCTION()
	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
private:
	float TimeOfEffect = 4000;
	
	float TimeOfEffectDilation = 4.f;

	void OnTimerExpired();

	FTimerManager* TimerManager = nullptr;

	FTimerHandle CooldownTimerHandle;
};
