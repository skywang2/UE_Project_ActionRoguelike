/*******************************************************************
*版权信息：Copyright ©2023-2024 wangzibin, All Rights Reserved.
*文件名称：
*文件标识：
*摘要：
*作者：wangzibin
*日期：2023
*备注：创建一个行为树task，从黑板获取目标位置，并从当前枪口生成子弹飞向目标
*
*当前版本：
*版本说明：新建
*******************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "SBTTask_RangedAttack.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API USBTTask_RangedAttack : public UBTTaskNode
{
	GENERATED_BODY()

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

public:
	UPROPERTY(EditAnywhere, Category = "AI_Set")
	TSubclassOf<AActor> projectileClass;
};
