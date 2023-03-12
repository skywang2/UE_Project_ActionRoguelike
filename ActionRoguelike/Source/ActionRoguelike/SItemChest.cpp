// Fill out your copyright notice in the Description page of Project Settings.


#include "SItemChest.h"

// Sets default values
ASItemChest::ASItemChest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_bashMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	RootComponent = m_bashMesh;

	m_lidMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LidMesh"));
	m_lidMesh->SetupAttachment(m_bashMesh);

	TargetPitch = 110.f;
}

void ASItemChest::Interact_Implementation(APawn* pawn)
{
	m_lidMesh->SetRelativeRotation(FRotator(TargetPitch, 0, 0));
}

// Called when the game starts or when spawned
void ASItemChest::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASItemChest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

