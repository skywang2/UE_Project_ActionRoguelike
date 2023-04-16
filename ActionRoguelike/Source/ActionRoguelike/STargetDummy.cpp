// Fill out your copyright notice in the Description page of Project Settings.


#include "STargetDummy.h"
#include "SAttributeComponent.h"

// Sets default values
ASTargetDummy::ASTargetDummy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_sphereComp = CreateDefaultSubobject<UStaticMeshComponent>("SphereComp");
	m_sphereComp->SetupAttachment(RootComponent);

	m_attributeComp = CreateDefaultSubobject<USAttributeComponent>("AttributeComp");
	m_attributeComp->m_OnHealthChanged.AddDynamic(this, &ASTargetDummy::HealthChanged);
}

void ASTargetDummy::HealthChanged(AActor* InstigatorActor, USAttributeComponent* OwningComp, float NewHealth, float Delta)
{
	//…˙√¸÷µºı…Ÿ
	if (Delta < 0.f)
	{
		m_sphereComp->SetScalarParameterValueOnMaterials("TimeToHit", GetWorld()->TimeSeconds);
	}
	UE_LOG(LogTemp, Display, TEXT("HealthChanged, at time:%f"), GetWorld()->TimeSeconds);
}
