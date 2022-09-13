// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "EnemyAIController.h"
#include "HeadToBomb.generated.h"

/**
 * 
 */
UCLASS()
class A1_API UHeadToBomb : public UBTTaskNode
{
	GENERATED_BODY()
		EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OnwerComp, uint8* NodeMemory) override;
	
};

