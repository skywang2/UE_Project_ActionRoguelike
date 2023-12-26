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


#include "Actors/SPowerup_HealthPotion.h"
#include "ActionRoguelike/SAttributeComponent.h"


ASPowerup_HealthPotion::ASPowerup_HealthPotion()
{
	m_MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	m_MeshComp->SetupAttachment(m_sphereComp);
	m_MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ASPowerup_HealthPotion::Interact_Implementation(APawn* instigator)
{
	if(!instigator)
	{
		UE_LOG(LogTemp, Log, TEXT("no instigator"));
		return;
	}
	
	USAttributeComponent* attributeComp = Cast<USAttributeComponent>(instigator->GetComponentByClass(USAttributeComponent::StaticClass()));
	if (attributeComp)
	{
		attributeComp->ApplyHealthChange(m_healVal);//改变血量
		UE_LOG(LogTemp, Log, TEXT("hit object has attributecomp"));
		HideAndCooldownPowerup();
	}
}
