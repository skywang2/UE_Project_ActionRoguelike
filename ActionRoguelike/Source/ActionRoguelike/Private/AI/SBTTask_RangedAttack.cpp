// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SBTTask_RangedAttack.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"

EBTNodeResult::Type USBTTask_RangedAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* controller = OwnerComp.GetAIOwner();
	if(ensure(controller))
	{
		ACharacter* pawn = Cast<ACharacter>(controller->GetPawn());
		if(!pawn)
		{
			return EBTNodeResult::Failed;
		}
		
		//获取模型枪口的位置
		FVector muzzleLocation = pawn->GetMesh()->GetSocketLocation("Muzzle_Front");
		//获取黑板中记录的目标位置
		UBlackboardComponent* blackboard = OwnerComp.GetBlackboardComponent();
		if(!blackboard)
		{
			return EBTNodeResult::Failed;			
		}
		AActor* target = Cast<AActor>(blackboard->GetValueAsObject("TargetActor"));
		FVector targetLocation = target->GetActorLocation();
		
		//生成子弹并拥有初始方向、速度
		FVector muzzleDirection = targetLocation - muzzleLocation;
		FRotator muzzleRotation = muzzleDirection.Rotation();
		FActorSpawnParameters spawnParam;
		spawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		AActor* projectile = GetWorld()->SpawnActor<AActor>(projectileClass, muzzleLocation, muzzleRotation, spawnParam);

		return projectile ? EBTNodeResult::Succeeded : EBTNodeResult::Failed;
	}
	
	return EBTNodeResult::Failed;
}
