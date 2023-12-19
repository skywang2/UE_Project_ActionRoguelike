// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActionRoguelike/SGameplayInterface.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "SPowerupActor.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API ASPowerupActor : public AActor, public ISGameplayInterface
{
	GENERATED_BODY()
public:
	ASPowerupActor();

	//触发ISGameplayInterface对象的Interact函数时，会自动调用该函数
	void Interact_Implementation(APawn* pawn);

protected:
	UPROPERTY(VisibleAnywhere)
	USphereComponent* m_sphereComp;//网格组件

	UPROPERTY()
	double m_respawnTime;
};
