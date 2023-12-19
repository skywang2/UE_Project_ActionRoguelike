/*******************************************************************
*版权信息：Copyright xxxxxxxxxxxxxxxxxxxxxx
*文件名称：
*文件标识：
*摘要：
*作者：wangzibin
*日期：20230313
*备注：定义Actor组件类，用于检测宝箱并触发其交互函数
*	  该交互对象用于处理人机交互，由键盘、鼠标事件处理函数触发，通过将处理方法封装到统一的交互类中，实现交互功能组件化
*
*当前版本：
*版本说明：新建
*******************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SInteractionComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTIONROGUELIKE_API USInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USInteractionComponent();

	void PrimaryInteract();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
