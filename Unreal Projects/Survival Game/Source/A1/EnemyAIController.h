// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "A1Character.h"
#include "TimeBomb.h"
#include "EnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class A1_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()

public:
	AEnemyAIController();

	virtual void BeginPlay() override;
	virtual void OnPossess(APawn*InPawn) override;
	virtual void Tick(float DeltaSeconds) override;
	virtual FRotator GetControlRotation() const override;
	void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;

	void GenerateNewRandomLocation();
	void HeadToBomb();
	void GetPartolRoute();

	//int32 TargetCheckpoint;

	UPROPERTY(EditAnywhere)
		TArray<FVector>Checkpoints;

	/*UFUNCTION()
	void OnPawnDetected(const TArray<AActor*>& DetectedPawns);
*/
	UFUNCTION()
		void OnSensesUpdated(AActor* UpdatedActor, FAIStimulus Stimulus);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI);
	float SightRadius = 500;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI);
	float SightAge = 3;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI);
	float LoseSightRadius = SightRadius + 30;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI);
	float FieldOfView = 45;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI);
	UAISenseConfig_Sight* SightConfiguration;

	UNavigationSystemV1* NavigationSystem;
	APawn* TargetPlayer;

	UPROPERTY(EditDefaultsOnly, Category = Blackboard)
		UBlackboardData* AIBlackboard;

	UPROPERTY(EditDefaultsOnly, Category = Blackboard)
		UBehaviorTree* BehaviorTree;

	//UPROPERTY(EditDefaultsOnly, Category = Blackboard)
		FBlackboardKeySelector* BB_AddPathIndex;


	//UPROPERTY(EditDefaultsOnly, Category = Blackboard)
		FBlackboardKeySelector* BB_PathVector;

	UPROPERTY(EditDefaultsOnly, Category = Blackboard)
		UBlackboardComponent* BlackboardComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool underAttack;


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "target")
		class AA1Character* target;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "target")
		class ATimeBomb* targetBomb;


	bool doOnce;
	bool BombdoOnce;

	bool hasExplode;

	FVector BombLocation;
	
	bool beingDistracted;
	bool distractedOnce;

	bool isStun;
};
