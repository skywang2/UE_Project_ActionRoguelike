// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SGameplayInterface.h"
#include "SItemChest.generated.h"

UCLASS()
class ACTIONROGUELIKE_API ASItemChest : public AActor, public ISGameplayInterface
{
	GENERATED_BODY()

	//����ISGameplayInterface�����Interact����ʱ�����Զ����øú���
	void Interact_Implementation(APawn* pawn);

protected:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* m_bashMesh;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* m_lidMesh;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Sets default values for this actor's properties
	ASItemChest();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
