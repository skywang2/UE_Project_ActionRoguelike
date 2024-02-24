// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SAICharacter.h"

#include "AIController.h"
#include "AIHelpers.h"
#include "BrainComponent.h"
#include "ActionRoguelike/SAttributeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/PawnSensingComponent.h"

ASAICharacter::ASAICharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//创建感知组件
	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>("PawnSensingComp");

	//添加属性组件
	m_attributeComp = CreateDefaultSubobject<USAttributeComponent>("AttributeComponent");
}

void ASAICharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	PawnSensingComp->OnSeePawn.AddDynamic(this, &ASAICharacter::OnPawnSeen);
	m_attributeComp->m_OnHealthChanged.AddDynamic(this, &ASAICharacter::OnHealthChanged);
}

void ASAICharacter::SetTargetActor(AActor* NewTarget)
{
	AAIController* AIC = Cast<AAIController>(GetController());
	if(AIC)
	{
		UBlackboardComponent* blackBoard = AIC->GetBlackboardComponent();
		if(blackBoard)
		{
			blackBoard->SetValueAsObject("TargetActor", NewTarget);
		}
	}
}

void ASAICharacter::OnHealthChanged(AActor* InstigatorActor, USAttributeComponent* OwningComp, float NewHealth,
                                    float Delta)
{
	if(InstigatorActor != this)
	{
		SetTargetActor(InstigatorActor);// 谁打机器人，机器人就打谁
	}
	
	if(Delta < 0.f)
	{
		if(NewHealth <= 0.f)// 生命小于0则停止AI控制器，并启用物理倒地效果，延迟删除对象
		{
			AAIController* AIC = Cast<AAIController>(GetController());
			if(AIC)
			{
				AIC->GetBrainComponent()->StopLogic("killed");
			}
			// ragdoll，布娃娃物理效果，角色倒地时使用
			GetMesh()->SetAllBodiesSimulatePhysics(true);//全身模型使用物理效果
			GetMesh()->SetCollisionProfileName("ragdoll");
			//延迟删除该对象
			SetLifeSpan(3.f);
		}
	}
}

void ASAICharacter::OnPawnSeen(APawn* Pawn)
{
	SetTargetActor(Pawn);//机器人看到谁就打谁
	UE_LOG(LogTemp, Display, TEXT("robot see something"));
}
