/*******************************************************************
*版权信息：Copyright ©2023-2024 wangzibin, All Rights Reserved.
*文件名称：
*文件标识：
*摘要：
*作者：wangzibin
*日期：20240209
*备注：定义机器人血条UI，用于跟随机器人显示伤害等，该类功能上只负责更新血条显示位置
*
*当前版本：
*版本说明：新建
*******************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SWorldUserWidget.generated.h"

class USizeBox;

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API USWorldUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, Category = "UI")
	AActor* AttachedActor;
	
protected:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	FVector WordOffset;
	
	UPROPERTY(meta = (BindWidget))
	USizeBox* ParentSizeBox;
};
