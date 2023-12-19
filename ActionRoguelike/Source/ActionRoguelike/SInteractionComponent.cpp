#include "SInteractionComponent.h"
#include "SGameplayInterface.h"

USInteractionComponent::USInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

//#define LineTrace

//实现查找交互可对象；调用交互对象的交互函数
void USInteractionComponent::PrimaryInteract()
{
	FCollisionObjectQueryParams objectQueryParams;
	objectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);//添加被碰撞检测的类型

	AActor* owner = GetOwner();//获取组件所有者

	FVector EyeLocation;
	FRotator EyeRotation;
	owner->GetActorEyesViewPoint(EyeLocation, EyeRotation);//获取Actor的相机位置和姿态

	FVector end = EyeLocation + EyeRotation.Vector() * 1000;//vector()可能返回单位向量，1000单位是厘米

#ifdef LineTrace	
	FHitResult hit;
	bool bBlockingHit = GetWorld()->LineTraceSingleByObjectType(hit, EyeLocation, end, objectQueryParams);
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
#else
	TArray<FHitResult> hits;

	float Radius = 30.f;
	FCollisionShape shape;//碰撞检测的形状
	shape.SetSphere(Radius);
	
	bool bBlockingHit = GetWorld()->SweepMultiByObjectType(hits, EyeLocation, end, FQuat::Identity, objectQueryParams, shape);
	FColor lineColor = bBlockingHit ? FColor::Green : FColor::Red;
	for (auto& hit : hits)
	{
		AActor* hitActor = hit.GetActor();
		if (hitActor)
		{
			if (hitActor->Implements<USGameplayInterface>())
			{
				APawn* pawn = Cast<APawn>(owner);//UE定义的安全类型转换

				ISGameplayInterface::Execute_Interact(hitActor, pawn);//触发hitActor的交互函数，入参是pawn
			}
			DrawDebugSphere(GetWorld(), hit.ImpactPoint, 10.f, 32, lineColor, false, 2.f, 0, 2.f);//在碰撞检测击中宝箱的位置画一个球
			break;
		}
	}
	DrawDebugLine(GetWorld(), EyeLocation, end, lineColor, false, 2.f, 0, 2.f);//绘制一条指向宝箱的线段
#endif

}

// Called when the game starts
void USInteractionComponent::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void USInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

