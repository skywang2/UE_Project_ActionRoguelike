/*******************************************************************
*��Ȩ��Ϣ��Copyright xxxxxxxxxxxxxxxxxxxxxx
*�ļ����ƣ�
*�ļ���ʶ��
*ժҪ��
*���ߣ�wangzibin
*���ڣ�20230405
*��ע�����ڲ�������Ч����Actor��
*
*��ǰ�汾��
*�汾˵�����½�
*******************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STargetDummy.generated.h"

class USAttributeComponent;

UCLASS()
class ACTIONROGUELIKE_API ASTargetDummy : public AActor
{
	GENERATED_BODY()

public:
	ASTargetDummy();

protected:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* m_sphereComp;

	UPROPERTY(VisibleAnywhere)
	USAttributeComponent* m_attributeComp;

	UFUNCTION()
	void HealthChanged(AActor* InstigatorActor, USAttributeComponent* OwningComp, float NewHealth, float Delta);//�����¼�������
};
