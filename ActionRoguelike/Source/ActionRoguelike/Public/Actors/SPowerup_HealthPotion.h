/*******************************************************************
*版权信息：Copyright xxxxxxxxxxxxxxxxxxxxxx
*文件名称：
*文件标识：
*摘要：
*作者：wangzibin
*日期：20231221
*备注：加血道具-治疗瓶
*
*当前版本：
*版本说明：新建
*******************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "SPowerupActor.h"
#include "SPowerup_HealthPotion.generated.h"

UCLASS()
class ACTIONROGUELIKE_API ASPowerup_HealthPotion : public ASPowerupActor
{
	GENERATED_BODY()

public:
	ASPowerup_HealthPotion();

	//触发ISGameplayInterface对象的Interact函数时，会自动调用该函数
	virtual void Interact_Implementation(APawn* instigator) override;

protected:
	UPROPERTY(VisibleAnywhere, Category="Component")
	UStaticMeshComponent* m_MeshComp;
};
