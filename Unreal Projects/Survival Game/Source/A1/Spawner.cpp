// Fill out your copyright notice in the Description page of Project Settings.


#include "Spawner.h"

// Sets default values
ASpawner::ASpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	StartText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("StartNumber"));
	StartText->SetHorizontalAlignment(EHTA_Center); //aline text 
	StartText->SetWorldSize(150.0f);
	RootComponent = StartText;


	SpawnInterval = 3;
	StartTime = 3;
	SpawnCountdown = 0;
	PitchValue = 0.f;
	YawValue = 0.f;
	RollValue = 0.f;
}

// Called when the game starts or when spawned
void ASpawner::BeginPlay()
{
	Super::BeginPlay();
	UpdateTimerDisplay();
	GetWorldTimerManager().SetTimer(StartTimerHandle, this, &ASpawner::AdvanceTimer, 1.0f, true);
}

// Called every frame
void ASpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	/*
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ANeedleTrap::StaticClass(), FoundActors);
	for (AActor* TActor : FoundActors)
	{
		ANeedleTrap* MyActor = Cast<ANeedleTrap>(TActor);

		if (MyActor == nullptr) {
			agent1 = 0;
		}

	}*/


	if (StartSpawning) {
		SpawnCountdown -= DeltaTime;
		if (SpawnCountdown <= 0) {
			
			AActor* tempReference = GetWorld()->SpawnActor<AActor>(SpawnObject, this->GetActorLocation(), FRotator::ZeroRotator);
			
			SpawnCountdown = SpawnInterval;

		}

		

			

		}

	}

void ASpawner::UpdateTimerDisplay() {
	//get start time float and round up 
	StartText->SetText(FString::FromInt(FMath::Max(StartTime, 0)));
}
void ASpawner::AdvanceTimer() {
	--StartTime;
	UpdateTimerDisplay();
	if (StartTime < 1) {
		//done countdown, and thus stop running the timer
		GetWorldTimerManager().ClearTimer(StartTimerHandle);
		CountdownHasFinished();

	}
}
void ASpawner::CountdownHasFinished() {
	StartText->SetText(TEXT(" "));

	StartSpawning = true;
}
