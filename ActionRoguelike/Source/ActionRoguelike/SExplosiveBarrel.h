/*******************************************************************
*��Ȩ��Ϣ��Copyright xxxxxxxxxxxxxxxxxxxxxx
*�ļ����ƣ�
*�ļ���ʶ��
*ժҪ��
*���ߣ�wangzibin
*���ڣ�20230313
*��ע�����屬ըͰ�࣬�������ʼ����
*	Actor���������ĵ���https://docs.unrealengine.com/5.1/zh-CN/unreal-engine-actor-lifecycle/
*
*��ǰ�汾��
*�汾˵�����½�
*******************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
//#include "PhysicsEngine/RadialForceComponent.h"
#include "SExplosiveBarrel.generated.h"

class UStaticMeshComponent;
class URadialForceComponent;

UCLASS()
class ACTIONROGUELIKE_API ASExplosiveBarrel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASExplosiveBarrel();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* m_meshComp;

	UPROPERTY(VisibleAnywhere)
	URadialForceComponent* m_forceComp;

	//�ڸ������������ʼ�������
	virtual void PostInitializeComponents() override;

	//��Actor���е���Ӧ����
	UFUNCTION()
	void OnActorHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit); 

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
