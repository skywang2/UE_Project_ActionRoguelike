/*******************************************************************
*版权信息：Copyright xxxxxxxxxxxxxxxxxxxxxx
*文件名称：
*文件标识：
*摘要：
*作者：wangzibin
*日期：20230311
*备注：定义一个宝箱类，使用多继承来扩展交互操作（可能）
*
*当前版本：
*版本说明：新建
*******************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SGameplayInterface.h"
#include "SItemChest.generated.h"

UCLASS()
class ACTIONROGUELIKE_API ASItemChest : public AActor, public ISGameplayInterface
{
	GENERATED_BODY()

	//触发ISGameplayInterface对象的Interact函数时，会自动调用该函数
	void Interact_Implementation(APawn* pawn);

protected:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* m_bashMesh;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* m_lidMesh;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Sets default values for this actor's properties
	ASItemChest();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
