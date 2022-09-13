// Fill out your copyright notice in the Description page of Project Settings.


#include "HeadToBomb.h"
EBTNodeResult::Type UHeadToBomb::ExecuteTask(UBehaviorTreeComponent & OnwerComp, uint8 * NodeMemory)
{
	UBehaviorTreeComponent* Component = &OnwerComp;
	if (!Component) { return EBTNodeResult::Failed; }

	AEnemyAIController* MyController = Cast<AEnemyAIController>(Component->GetOwner());
	if (!MyController) { return EBTNodeResult::Failed; }

	MyController->HeadToBomb();
	return EBTNodeResult::Succeeded;
}
