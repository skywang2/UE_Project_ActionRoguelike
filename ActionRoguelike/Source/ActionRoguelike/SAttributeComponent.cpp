// Fill out your copyright notice in the Description page of Project Settings.


#include "SAttributeComponent.h"

// Sets default values for this component's properties
USAttributeComponent::USAttributeComponent()
	:m_health(100.f)
{

}

bool USAttributeComponent::ApplyHealthChange(float Delta)
{
	m_health += Delta;

	m_OnHealthChanged.Broadcast(nullptr, this, m_health, Delta);//发出血量改变事件广播

	return false;
}
