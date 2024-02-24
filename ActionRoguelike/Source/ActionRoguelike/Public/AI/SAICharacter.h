// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SAICharacter.generated.h"

class UPawnSensingComponent;
class USAttributeComponent;

UCLASS()
class ACTIONROGUELIKE_API ASAICharacter : public ACharacter
{
	GENERATED_BODY()
protected:
	virtual void PostInitializeComponents() override;

	void SetTargetActor(AActor* NewTarget);
	
	UFUNCTION()
	void OnHealthChanged(AActor* InstigatorActor, USAttributeComponent* OwningComp, float NewHealth, float Delta);
	
	UFUNCTION()
	void OnPawnSeen(APawn* Pawn);	
	
	UPROPERTY(VisibleAnywhere, Category="Componens")
	UPawnSensingComponent* PawnSensingComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	USAttributeComponent* m_attributeComp;

public:
	ASAICharacter();
};
