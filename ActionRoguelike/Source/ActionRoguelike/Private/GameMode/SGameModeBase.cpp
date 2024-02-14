// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/SGameModeBase.h"

#include "EnvironmentQuery/EnvQueryManager.h"

ASGameModeBase::ASGameModeBase()
	:SpawnTimerInterval(2.f)
{
}

void ASGameModeBase::StartPlay()
{
	Super::StartPlay();

	GetWorldTimerManager().SetTimer(TimerHandle_SpawnBots, this, &ASGameModeBase::SpawnTimerElapsed, SpawnTimerInterval);
}

void ASGameModeBase::SpawnTimerElapsed()
{
	UEnvQueryInstanceBlueprintWrapper* queryInstance = UEnvQueryManager::RunEQSQuery(this, SpawnBotQuery, this, EEnvQueryRunMode::RandomBest5Pct, nullptr);

	if(ensure(queryInstance))
	{
		queryInstance->GetOnQueryFinishedEvent().AddDynamic(this, &ASGameModeBase::OnQueryCompleted);
	}
}

void ASGameModeBase::OnQueryCompleted(UEnvQueryInstanceBlueprintWrapper* QueryInstance,
	EEnvQueryStatus::Type QueryStatus)
{
	if(QueryStatus != EEnvQueryStatus::Success)
	{
		UE_LOG(LogTemp, Warning, TEXT("Spawn bot EQS Query Failed. %s"), "this is addition things.");
		return;
	}
	TArray<FVector> locations;
	
	bool ret = QueryInstance->GetQueryResultsAsLocations(locations);
	if(ret && locations.IsValidIndex(0))
	{
		AActor* actor = GetWorld()->SpawnActor<AActor>(MinionClass, locations[0], FRotator::ZeroRotator);		
	}
	
}
