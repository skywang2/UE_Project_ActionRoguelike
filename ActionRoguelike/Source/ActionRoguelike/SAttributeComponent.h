/*******************************************************************
*��Ȩ��Ϣ��Copyright xxxxxxxxxxxxxxxxxxxxxx
*�ļ����ƣ�
*�ļ���ʶ��
*ժҪ��
*���ߣ�wangzibin
*���ڣ�20230405
*��ע�������ɫ������������ڱ��桢����������ԣ���Ѫ������������
*
*��ǰ�汾��
*�汾˵�����½�
*******************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SAttributeComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTIONROGUELIKE_API USAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USAttributeComponent();	

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	bool ApplyHealthChange(float Delta);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Attributes")
	float m_health;

};
