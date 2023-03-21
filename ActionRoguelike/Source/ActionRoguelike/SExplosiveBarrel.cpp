// Fill out your copyright notice in the Description page of Project Settings.


#include "SExplosiveBarrel.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "SMagicProjectile.h"

// Sets default values
ASExplosiveBarrel::ASExplosiveBarrel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_meshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	m_meshComp->SetupAttachment(RootComponent);
	m_meshComp->SetSimulatePhysics(true);

	m_forceComp = CreateDefaultSubobject<URadialForceComponent>("ForceComp");
	m_forceComp->SetupAttachment(m_meshComp);
	m_forceComp->SetAutoActivate(false);//不自动激活

	m_forceComp->Radius = 500.f;//半径
	m_forceComp->ImpulseStrength = 1500.f;//冲量大小，如果bImpulseVelChange = false，则需要至少200000.f才能由明显效果
	m_forceComp->bImpulseVelChange = true;
	m_forceComp->AddCollisionChannelToAffect(ECC_WorldDynamic);//在细节-径向力组件-要影响的对象类型
	//需要开启模拟命中事件，并过滤碰撞时的Actor对象
}

// Called when the game starts or when spawned
void ASExplosiveBarrel::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASExplosiveBarrel::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	//注册碰撞响应函数
	m_meshComp->OnComponentHit.AddDynamic(this, &ASExplosiveBarrel::OnActorHit);
}

void ASExplosiveBarrel::OnActorHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{

	if (ASMagicProjectile* HitActor = Cast<ASMagicProjectile>(OtherActor))
	{
		m_forceComp->FireImpulse();//对半径内的对象发射径向力
	}
}

// Called every frame
void ASExplosiveBarrel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

