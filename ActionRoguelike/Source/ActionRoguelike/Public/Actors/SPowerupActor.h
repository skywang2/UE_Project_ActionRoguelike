/*******************************************************************
*版权信息：Copyright xxxxxxxxxxxxxxxxxxxxxx
*文件名称：
*文件标识：
*摘要：
*作者：wangzibin
*日期：20231219
*备注：加血道具公共类
*
*当前版本：
*版本说明：新建
*******************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "ActionRoguelike/SGameplayInterface.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "SPowerupActor.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API ASPowerupActor : public AActor, public ISGameplayInterface
{
	GENERATED_BODY()
public:
	ASPowerupActor();

	//触发ISGameplayInterface对象的Interact函数时，会自动调用该函数
	virtual void Interact_Implementation(APawn* instigator);

protected:
	void ShowPowerup();

	void HideAndCooldownPowerup();

	void SetPowerupState(bool bIsActive);
	
protected:
	UPROPERTY(VisibleAnywhere, Category = "Component")
	USphereComponent* m_sphereComp;//网格组件

	FTimerHandle m_respawnTimeHandle;
	
	UPROPERTY(EditAnywhere, Category = "Powerup")
	double m_respawnTime;

	UPROPERTY(EditAnywhere, Category = "Powerup")
	double m_healVal;

};
