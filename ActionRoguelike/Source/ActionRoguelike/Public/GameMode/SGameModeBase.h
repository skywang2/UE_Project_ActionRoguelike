/*******************************************************************
*版权信息：Copyright ©2023-2023 wangzibin, All Rights Reserved.
*文件名称：
*文件标识：
*摘要：
*作者：wangzibin
*日期：20240214
*备注：定义一个GameMode，用于定时生成AI对象
*
*当前版本：
*版本说明：新建
*******************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "GameFramework/GameModeBase.h"
#include "SGameModeBase.generated.h"

class UEnvQuery;
class UEnvQueryInstanceBlueprintWrapper;

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API ASGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, Category="AI")
	UCurveFloat* DifficultyCurve;
	
	UPROPERTY(EditDefaultsOnly, Category="AI")
	TSubclassOf<AActor> MinionClass;//需要生成的对象
	
	UPROPERTY(EditDefaultsOnly, Category="AI")
	UEnvQuery* SpawnBotQuery;//生成位置查询
	
	FTimerHandle TimerHandle_SpawnBots;//定时器，生成机器人

	UPROPERTY(EditDefaultsOnly, Category="AI")
	float SpawnTimerInterval;//定时器持续时间

	void SpawnTimerElapsed();//定时器回调函数
	
	UFUNCTION()
	void OnQueryCompleted(UEnvQueryInstanceBlueprintWrapper* QueryInstance, EEnvQueryStatus::Type QueryStatus);
	
public:
	ASGameModeBase();

	virtual void StartPlay() override;
};
