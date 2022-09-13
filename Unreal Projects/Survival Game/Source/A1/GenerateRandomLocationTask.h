// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "EnemyAIController.h"
#include "GenerateRandomLocationTask.generated.h"

/**
 * 
 */
UCLASS()
class A1_API UGenerateRandomLocationTask : public UBTTaskNode
{
	GENERATED_BODY()
		EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OnwerComp, uint8* NodeMemory) override;
};
