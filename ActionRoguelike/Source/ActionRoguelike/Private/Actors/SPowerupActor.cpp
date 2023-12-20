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


#include "Actors/SPowerupActor.h"


ASPowerupActor::ASPowerupActor()
	:m_respawnTime(5.0),
	m_healVal(10.0)
{
	m_sphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	m_sphereComp->SetupAttachment(RootComponent);	
}

void ASPowerupActor::Interact_Implementation(APawn* instigator)
{
}

void ASPowerupActor::ShowPowerup()
{
	SetPowerupState(true);
}

void ASPowerupActor::HideAndCooldownPowerup()
{
	SetPowerupState(false);

	GetWorldTimerManager().SetTimer(m_respawnTimeHandle, this, &ASPowerupActor::ShowPowerup, m_respawnTime);
}

//是否开启碰撞、是否可见
void ASPowerupActor::SetPowerupState(bool bIsActive)
{
	SetActorEnableCollision(bIsActive);//是否开启碰撞检测

	RootComponent->SetVisibility(bIsActive, true);//第二个参数应该是选择是否影响子组件
}
