/*******************************************************************
*版权信息：Copyright ©2023-2023 wangzibin, All Rights Reserved.
*文件名称：
*文件标识：
*摘要：
*作者：wangzibin
*日期：20230405
*备注：定义角色属性组件，用于保存、计算各种属性，如血量、攻击力等
*
*当前版本：
*版本说明：新建
*******************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Delegates/DelegateCombinations.h"
#include "SAttributeComponent.generated.h"

//创建生命值改变事件代理
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnHealthChanged/*事件名*/, AActor*, InstigatorActor, USAttributeComponent*, OwningComp, float, NewHealth, float, Delta);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTIONROGUELIKE_API USAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USAttributeComponent();	

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	bool ApplyHealthChange(AActor* InstigatorActor, float Delta);

	UFUNCTION(BlueprintCallable, Category = "MyFunctions")
	bool IsAlive();

	static bool IsAlive(AActor* actor);

	UFUNCTION(BlueprintCallable)
	static USAttributeComponent* GetAttributes(AActor* FromActor);
	
	UPROPERTY(BlueprintAssignable)
	FOnHealthChanged m_OnHealthChanged;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Attributes")
	float m_health;//当前生命

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Attributes")
	float m_maxHealth;//生命上限
};
