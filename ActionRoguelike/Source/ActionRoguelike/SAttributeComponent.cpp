// Fill out your copyright notice in the Description page of Project Settings.


#include "SAttributeComponent.h"

// Sets default values for this component's properties
USAttributeComponent::USAttributeComponent()
	:m_health(100.f)
{

}

bool USAttributeComponent::ApplyHealthChange(AActor* InstigatorActor, float Delta)
{
	m_health += Delta;
	m_health = (m_health < m_maxHealth) ? m_health : m_maxHealth;

	m_OnHealthChanged.Broadcast(InstigatorActor, this, m_health, Delta);//发出血量改变事件广播

	return false;
}

bool USAttributeComponent::IsAlive()
{
	return m_health > 0.f;
}
