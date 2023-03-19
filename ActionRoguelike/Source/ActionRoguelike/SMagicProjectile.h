/*******************************************************************
*版权信息：Copyright xxxxxxxxxxxxxxxxxxxxxx
*文件名称：
*文件标识：
*摘要：
*作者：wangzibin
*日期：20230311
*备注：抛射物类型
*
*当前版本：
*版本说明：新建
*******************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SMagicProjectile.generated.h"
class USphereComponent;
class UProjectileMovementComponent;
class UParticleSystemComponent;

UCLASS()
class ACTIONROGUELIKE_API ASMagicProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASMagicProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USphereComponent* m_sphereComp;

	UPROPERTY(VisibleAnywhere)
	UProjectileMovementComponent* m_movementComp;

	UPROPERTY(VisibleAnywhere)
	UParticleSystemComponent* m_particleComp;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
