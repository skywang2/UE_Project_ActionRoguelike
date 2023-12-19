// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/SPowerupActor.h"

#include "ActionRoguelike/SAttributeComponent.h"

ASPowerupActor::ASPowerupActor()
	:m_respawnTime(10.0)
{
	m_sphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	m_sphereComp->SetupAttachment(RootComponent);
	
}

void ASPowerupActor::Interact_Implementation(APawn* pawn)
{
	if(ensure(pawn))
	{
		USAttributeComponent* attributeComp = Cast<USAttributeComponent>(pawn->GetComponentByClass(USAttributeComponent::StaticClass()));
		if (attributeComp)
		{
			attributeComp->ApplyHealthChange(m_respawnTime);//改变血量
			UE_LOG(LogTemp, Log, TEXT("hit object has attributecomp"));
		}
	}
}
