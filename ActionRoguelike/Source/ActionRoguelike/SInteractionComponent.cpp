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

//#define LineTrace

//ʵ�ֲ��ҽ����ɶ��󣻵��ý�������Ľ�������
void USInteractionComponent::PrimaryInteract()
{
	FCollisionObjectQueryParams objectQueryParams;
	objectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);//��ӱ���ײ��������

	AActor* owner = GetOwner();//��ȡ���������

	FVector EyeLocation;
	FRotator EyeRotation;
	owner->GetActorEyesViewPoint(EyeLocation, EyeRotation);//��ȡActor�����λ�ú���̬

	FVector end = EyeLocation + EyeRotation.Vector() * 1000;//vector()���ܷ��ص�λ������1000��λ������

#ifdef LineTrace	
	FHitResult hit;
	bool bBlockingHit = GetWorld()->LineTraceSingleByObjectType(hit, EyeLocation, end, objectQueryParams);
	AActor* hitActor = hit.GetActor();
	if (hitActor)
	{
		if (hitActor->Implements<USGameplayInterface>())
		{
			APawn* pawn = Cast<APawn>(owner);//UE����İ�ȫ����ת��

			ISGameplayInterface::Execute_Interact(hitActor, pawn);//����hitActor�Ľ��������������pawn
		}
	}

	FColor lineColor = bBlockingHit ? FColor::Green : FColor::Red;
	DrawDebugLine(GetWorld(), EyeLocation, end, lineColor, false, 2.f, 0, 2.f);//����һ��ָ������߶�
#else
	TArray<FHitResult> hits;

	float Radius = 30.f;
	FCollisionShape shape;//��ײ������״
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
				APawn* pawn = Cast<APawn>(owner);//UE����İ�ȫ����ת��

				ISGameplayInterface::Execute_Interact(hitActor, pawn);//����hitActor�Ľ��������������pawn
			}
			DrawDebugSphere(GetWorld(), hit.ImpactPoint, 10.f, 32, lineColor, false, 2.f, 0, 2.f);//����ײ�����б����λ�û�һ����
			break;
		}
	}
	DrawDebugLine(GetWorld(), EyeLocation, end, lineColor, false, 2.f, 0, 2.f);//����һ��ָ������߶�
#endif

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

