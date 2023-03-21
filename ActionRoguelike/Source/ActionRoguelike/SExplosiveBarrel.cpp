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
	m_forceComp->SetAutoActivate(false);//���Զ�����

	m_forceComp->Radius = 500.f;//�뾶
	m_forceComp->ImpulseStrength = 1500.f;//������С�����bImpulseVelChange = false������Ҫ����200000.f����������Ч��
	m_forceComp->bImpulseVelChange = true;
	m_forceComp->AddCollisionChannelToAffect(ECC_WorldDynamic);//��ϸ��-���������-ҪӰ��Ķ�������
	//��Ҫ����ģ�������¼�����������ײʱ��Actor����
}

// Called when the game starts or when spawned
void ASExplosiveBarrel::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASExplosiveBarrel::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	//ע����ײ��Ӧ����
	m_meshComp->OnComponentHit.AddDynamic(this, &ASExplosiveBarrel::OnActorHit);
}

void ASExplosiveBarrel::OnActorHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{

	if (ASMagicProjectile* HitActor = Cast<ASMagicProjectile>(OtherActor))
	{
		m_forceComp->FireImpulse();//�԰뾶�ڵĶ����侶����
	}
}

// Called every frame
void ASExplosiveBarrel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

