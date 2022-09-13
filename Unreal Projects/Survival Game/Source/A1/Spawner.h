// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include"Components/TextRenderComponent.h"
#include "NeedleTrap.h"
#include "Spawner.generated.h"

UCLASS()
class A1_API ASpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditAnywhere)
		float SpawnInterval;

	UPROPERTY(EditAnywhere)
		float Yaw;

	//time to start in s
	UPROPERTY(EditAnywhere)
		int32 StartTime;

	UPROPERTY(EditAnywhere, Category = "SpawnObject")
		TSubclassOf<AActor> SpawnObject;


	bool StartSpawning = false;
	float SpawnCountdown;


	UTextRenderComponent* StartText;


	//countdown functions
	void UpdateTimerDisplay();

	void AdvanceTimer();

	void CountdownHasFinished();

	//TimerHandle 
	FTimerHandle StartTimerHandle;

	UPROPERTY(EditAnywhere, Category = Movement)
		float PitchValue;

	UPROPERTY(EditAnywhere, Category = Movement)
		float YawValue;

	UPROPERTY(EditAnywhere, Category = Movement)
		float RollValue;

};
