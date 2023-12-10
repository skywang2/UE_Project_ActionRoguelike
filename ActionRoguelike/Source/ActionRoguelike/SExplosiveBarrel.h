/*******************************************************************
*版权信息：Copyright xxxxxxxxxxxxxxxxxxxxxx
*文件名称：
*文件标识：
*摘要：
*作者：wangzibin
*日期：20230313
*备注：定义爆炸桶类，在组件初始化后
*	Actor生命周期文档：https://docs.unrealengine.com/5.1/zh-CN/unreal-engine-actor-lifecycle/
*
*当前版本：
*版本说明：新建
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

	//在该类所有组件初始化后调用
	virtual void PostInitializeComponents() override;

	//被Actor击中的响应函数
	UFUNCTION()
	void OnActorHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit); 

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
