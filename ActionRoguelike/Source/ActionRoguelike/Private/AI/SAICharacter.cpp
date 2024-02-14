// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SAICharacter.h"

#include "ActionRoguelike/SAttributeComponent.h"
#include "Perception/PawnSensingComponent.h"

ASAICharacter::ASAICharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//创建感知组件
	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>("PawnSensingComp");

	//添加属性组件
	m_attributeComp = CreateDefaultSubobject<USAttributeComponent>("AttributeComponent");
}
