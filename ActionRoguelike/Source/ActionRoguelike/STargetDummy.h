/*******************************************************************
*版权信息：Copyright xxxxxxxxxxxxxxxxxxxxxx
*文件名称：
*文件标识：
*摘要：
*作者：wangzibin
*日期：20230405
*备注：用于测试纹理效果的Actor类
*
*当前版本：
*版本说明：新建
*******************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STargetDummy.generated.h"

class USAttributeComponent;

UCLASS()
class ACTIONROGUELIKE_API ASTargetDummy : public AActor
{
	GENERATED_BODY()

public:
	ASTargetDummy();

protected:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* m_sphereComp;

	UPROPERTY(VisibleAnywhere)
	USAttributeComponent* m_attributeComp;

	UFUNCTION()
	void HealthChanged(AActor* InstigatorActor, USAttributeComponent* OwningComp, float NewHealth, float Delta);//定义事件处理函数
};
