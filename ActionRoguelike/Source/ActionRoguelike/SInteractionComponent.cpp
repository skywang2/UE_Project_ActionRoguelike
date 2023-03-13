// Fill out your copyright notice in the Description page of Project Settings.


#include "SInteractionComponent.h"
#include "SGameplayInterface.h"

// Sets default values for this component's properties
USInteractionComponent::USInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void USInteractionComponent::PrimaryInteract()
{
	FCollisionObjectQueryParams queryParams;
	queryParams.AddObjectTypesToQuery(ECC_WorldDynamic);//添加被碰撞检测的类型

	AActor* owner = GetOwner();//获取组件所有者

	FVector EyeLocation;
	FRotator EyeRotation;
	owner->GetActorEyesViewPoint(EyeLocation, EyeRotation);//获取Actor的相机位置和姿态

	FVector end = EyeLocation + EyeRotation.Vector() * 1000;//vector()可能返回单位向量，1000单位是厘米

	FHitResult hit;
	bool bBlockingHit = GetWorld()->LineTraceSingleByObjectType(hit, EyeLocation, end, queryParams);

	AActor* hitActor = hit.GetActor();
	if (hitActor)
	{
		if (hitActor->Implements<USGameplayInterface>())
		{
			APawn* pawn = Cast<APawn>(owner);//UE定义的安全类型转换

			ISGameplayInterface::Execute_Interact(hitActor, pawn);//触发hitActor的交互函数，入参是pawn
		}
	}

	FColor lineColor = bBlockingHit ? FColor::Green : FColor::Red;
	DrawDebugLine(GetWorld(), EyeLocation, end, lineColor, false, 2.f, 0, 2.f);//绘制一条指向宝箱的线段
}

// Called when the game starts
void USInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void USInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

