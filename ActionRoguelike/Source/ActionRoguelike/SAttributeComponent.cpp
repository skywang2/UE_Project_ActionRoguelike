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

	return false;
}
