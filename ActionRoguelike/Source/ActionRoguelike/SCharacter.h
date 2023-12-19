/*******************************************************************
*版权信息：Copyright xxxxxxxxxxxxxxxxxxxxxx
*文件名称：
*文件标识：
*摘要：
*作者：wangzibin
*日期：20230311
*备注：角色类型
*
*当前版本：
*版本说明：新建
*******************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class USInteractionComponent;
class USAttributeComponent;

UCLASS()
class ACTIONROGUELIKE_API ASCharacter : public ACharacter
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category = "Attack")
	TSubclassOf<AActor> m_projectileClass;

	UPROPERTY(EditAnywhere, Category = "Attack")
	UAnimMontage* m_AttackAnim;

	FTimerHandle TimerHandle_PrimaryAttack;//子弹生成定时器

	TAtomic<bool> IsIEReleased;//鼠标松开事件是否正在处理，确保攻击动作能完整播放

public:
	// Sets default values for this character's properties
	ASCharacter();

protected:
	UPROPERTY(VisibleAnywhere)//在蓝图编辑页面可以看到该组件的所有属性，右侧面板
	USpringArmComponent* m_springArmComp;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* m_cameraComp;

	UPROPERTY(VisibleAnywhere)
	USInteractionComponent* m_interactComp;//交互组件

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	USAttributeComponent* m_attributeComp;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//键盘，向前移动
	void MoveForward(float value);
	//键盘，向右移动
	void MoveRight(float value);
	//键盘，跳起
	//void JumpUp();
	//发动攻击
	void PrimaryAttack();
	void PrimaryAttack_TimeElapsed();
	//与宝箱交互，触发
	void PrimaryInteract();

	UFUNCTION()
	void HealthChanged(AActor* InstigatorActor, USAttributeComponent* OwningComp, float NewHealth, float Delta);//定义事件处理函数

	virtual void PostInitializeComponents() override;//组件初始化后操作

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
