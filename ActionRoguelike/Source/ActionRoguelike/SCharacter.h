/*******************************************************************
*��Ȩ��Ϣ��Copyright xxxxxxxxxxxxxxxxxxxxxx
*�ļ����ƣ�
*�ļ���ʶ��
*ժҪ��
*���ߣ�wangzibin
*���ڣ�20230311
*��ע����ɫ����
*
*��ǰ�汾��
*�汾˵�����½�
*******************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class ACTIONROGUELIKE_API ASCharacter : public ACharacter
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> m_projectileClass;
public:
	// Sets default values for this character's properties
	ASCharacter();

protected:
	UPROPERTY(VisibleAnywhere)//����ͼ�༭ҳ����Կ�����������������ԣ��Ҳ����
	USpringArmComponent* m_springArmComp;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* m_cameraComp;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//���̣���ǰ�ƶ�
	void MoveForward(float value);
	//���̣������ƶ�
	void MoveRight(float value);
	//��������
	void PrimaryAttack();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
