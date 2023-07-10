// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SBTService_CheckAttackRange.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

//作用：检测AI对象与目标之间的距离

void USBTService_CheckAttackRange::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	//获取黑板指针
	UBlackboardComponent* blackboard = OwnerComp.GetBlackboardComponent();
	if(ensure(blackboard))
	{
		AActor* target = Cast<AActor>(blackboard->GetValueAsObject("TargetActor"));
		if(target)
		{
			AAIController* controller = OwnerComp.GetAIOwner();
			if(ensure(controller))
			{
				APawn* aiPawn = controller->GetPawn();
				if(ensure(aiPawn))
				{
					const float distanceTo = FVector::Distance(target->GetActorLocation(), aiPawn->GetActorLocation());
					bool bWithinRange = distanceTo < 2000.f;
					blackboard->SetValueAsBool(AttackRangeKey.SelectedKeyName, bWithinRange);//在编辑器中设置黑板变量
				}
			}
		}
	}
}
