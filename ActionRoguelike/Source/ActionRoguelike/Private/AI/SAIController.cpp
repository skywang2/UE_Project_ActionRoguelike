// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SAIController.h"

void ASAIController::BeginPlay()
{
	Super::BeginPlay();

	RunBehaviorTree(m_behaviorTree);
}
