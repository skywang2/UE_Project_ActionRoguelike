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
	queryParams.AddObjectTypesToQuery(ECC_WorldDynamic);//��ӱ���ײ��������

	AActor* owner = GetOwner();//��ȡ���������

	FVector EyeLocation;
	FRotator EyeRotation;
	owner->GetActorEyesViewPoint(EyeLocation, EyeRotation);//��ȡActor�����λ�ú���̬

	FVector end = EyeLocation + EyeRotation.Vector() * 1000;//vector()���ܷ��ص�λ������1000��λ������

	FHitResult hit;
	bool bBlockingHit = GetWorld()->LineTraceSingleByObjectType(hit, EyeLocation, end, queryParams);

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

