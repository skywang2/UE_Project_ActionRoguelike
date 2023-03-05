// Fill out your copyright notice in the Description page of Project Settings.


#include "SMagicProjectile.h"
#include "Components\SphereComponent.h"
#include "Particles\ParticleSystemComponent.h"
#include "GameFramework\ProjectileMovementComponent.h"

// Sets default values
ASMagicProjectile::ASMagicProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	m_sphereComp = CreateDefaultSubobject<USphereComponent>("sphereComp");
	m_sphereComp->SetCollisionObjectType(ECC_WorldDynamic);
	//m_sphereComp->SetCollisionResponseToAllChannels(ECR_Block);//对所有类型都设置碰撞
	//m_sphereComp->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Block);//对指定类型设置碰撞
	m_sphereComp->SetCollisionProfileName("coll_projectile");//使用自定义的碰撞配置
	RootComponent = m_sphereComp;
	
	m_particleComp = CreateDefaultSubobject<UParticleSystemComponent>("particleComp");
	m_particleComp->SetupAttachment(m_sphereComp);
	
	m_movementComp = CreateDefaultSubobject<UProjectileMovementComponent>("movementComp");
	m_movementComp->InitialSpeed = 1000.f;
	m_movementComp->bRotationFollowsVelocity = true;
	m_movementComp->bInitialVelocityInLocalSpace = true;
}

// Called when the game starts or when spawned
void ASMagicProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASMagicProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

