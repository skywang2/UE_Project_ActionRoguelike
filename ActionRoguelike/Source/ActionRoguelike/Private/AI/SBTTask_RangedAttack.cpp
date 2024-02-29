// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SBTTask_RangedAttack.h"

#include "AIController.h"
// #include "ModuleDescriptor.h"
#include "ActionRoguelike/SAttributeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"


USBTTask_RangedAttack::USBTTask_RangedAttack()
	:MaxBulletSpread(2.f)
{
}

/* brief 从黑板获取目标位置，并从当前枪口生成子弹飞向目标
 * ParamIn OwnerComp
 * ParamOut
 * Return Type
 */
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
		//获取目标对象
		AActor* target = Cast<AActor>(blackboard->GetValueAsObject("TargetActor"));
		if(nullptr == target)
		{
			return EBTNodeResult::Failed;
		}

		if(!USAttributeComponent::IsAlive(target))
		{
			return EBTNodeResult::Failed;
		}
		
		FVector targetLocation = target->GetActorLocation();
		
		//生成子弹并拥有初始方向、速度
		FVector muzzleDirection = targetLocation - muzzleLocation;
		FRotator muzzleRotation = muzzleDirection.Rotation();
		//给射击增加一些漂移
		muzzleRotation.Pitch += FMath::RandRange(-MaxBulletSpread, MaxBulletSpread);
		muzzleRotation.Yaw += FMath::RandRange(-MaxBulletSpread, MaxBulletSpread);
		//actor生成参数
		FActorSpawnParameters spawnParam;
		spawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		spawnParam.Instigator = pawn;
		AActor* projectile = GetWorld()->SpawnActor<AActor>(projectileClass, muzzleLocation, muzzleRotation, spawnParam);

		return projectile ? EBTNodeResult::Succeeded : EBTNodeResult::Failed;
	}
	
	return EBTNodeResult::Failed;
}
