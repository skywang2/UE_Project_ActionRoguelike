// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/SGameModeBase.h"

#include "EngineUtils.h"
#include "ActionRoguelike/SAttributeComponent.h"
#include "AI/SAICharacter.h"
#include "EnvironmentQuery/EnvQueryManager.h"

ASGameModeBase::ASGameModeBase()
	:SpawnTimerInterval(2.f)
{
}

void ASGameModeBase::StartPlay()
{
	Super::StartPlay();

	GetWorldTimerManager().SetTimer(TimerHandle_SpawnBots, this, &ASGameModeBase::SpawnTimerElapsed, SpawnTimerInterval, true);
}

void ASGameModeBase::SpawnTimerElapsed()
{
	int32 NrOfAliveBots = 0;
	for(TActorIterator<ASAICharacter> it(GetWorld()); it; ++it)
	{
		ASAICharacter* bot = *it;
		USAttributeComponent* attributeComp = Cast<USAttributeComponent>(bot->GetComponentByClass(USAttributeComponent::StaticClass()));
		if(ensure(attributeComp) && attributeComp->IsAlive())
		{
			NrOfAliveBots++;
		}
	}
	UE_LOG(LogTemp, Log, TEXT("Found %d alive bots."), NrOfAliveBots);
	//限制Bot数量
	float maxBotCount = 10.f;
	if(DifficultyCurve)
	{
		maxBotCount = DifficultyCurve->GetFloatValue(GetWorld()->TimeSeconds);
	}
	if(NrOfAliveBots >= maxBotCount)
	{
		return;
	}

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
	UE_LOG(LogTemp, Log, TEXT("Query locations count is %d."), locations.Num());
	if(ret && locations.IsValidIndex(0))
	{
		AActor* actor = GetWorld()->SpawnActor<AActor>(MinionClass, locations[0], FRotator::ZeroRotator);		
	}
	
}
