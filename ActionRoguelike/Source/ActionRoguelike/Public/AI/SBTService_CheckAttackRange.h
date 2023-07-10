// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "SBTService_CheckAttackRange.generated.h"

/**
 * AI服务，检测AI对象到目标是否在指定距离内
 */
UCLASS()
class ACTIONROGUELIKE_API USBTService_CheckAttackRange : public UBTService
{
	GENERATED_BODY()

protected:
	//在行为树-服务节点上显示选变量的下拉列表，这样可以在界面上选择要读取的黑板变量，不必硬编码
	UPROPERTY(EditAnywhere, Category = "AI_Set")
	FBlackboardKeySelector AttackRangeKey;
	
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
