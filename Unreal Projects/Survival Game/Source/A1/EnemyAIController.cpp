// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"
#include"GameFramework/CharacterMovementComponent.h"
#include "GameFramework/InputSettings.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"

AEnemyAIController::AEnemyAIController() {
	PrimaryActorTick.bCanEverTick = true;
	SightConfiguration = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Configuration"));
	SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Preception Component")));

	SightConfiguration->SightRadius = SightRadius;
	SightConfiguration->LoseSightRadius = LoseSightRadius;
	SightConfiguration->PeripheralVisionAngleDegrees = FieldOfView;
	SightConfiguration->SetMaxAge(SightAge);

	SightConfiguration->DetectionByAffiliation.bDetectEnemies = true;
	SightConfiguration->DetectionByAffiliation.bDetectFriendlies = true;
	SightConfiguration->DetectionByAffiliation.bDetectNeutrals = true;

	GetPerceptionComponent()->SetDominantSense(*SightConfiguration->GetSenseImplementation());
	GetPerceptionComponent()->ConfigureSense(*SightConfiguration);
	GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, &AEnemyAIController::OnSensesUpdated);
	//GetPerceptionComponent()->OnPerceptionUpdated.AddDynamic(this, &AEnemyAIController::OnPawnDetected);

	TargetPlayer = nullptr;

	doOnce = false;
	BombdoOnce = false;
	hasExplode = false;
	beingDistracted = false;
	isStun = false;
	distractedOnce = false;
}
void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();

	if (!AIBlackboard) { return; }
	if (!ensure(BehaviorTree)) { return; }
	UseBlackboard(AIBlackboard, BlackboardComponent);
	RunBehaviorTree(BehaviorTree);
	NavigationSystem = Cast<UNavigationSystemV1>(GetWorld()->GetNavigationSystem());
	GenerateNewRandomLocation();
	HeadToBomb();

	/*
	TArray <AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AA1Character::StaticClass(), FoundActors);
	myCharacter = Cast<AA1Character>(FoundActors[0]);*/
}

void AEnemyAIController::OnPossess(APawn * InPawn)
{
	Super::OnPossess(InPawn);
}

void AEnemyAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (TargetPlayer) {
		BlackboardComponent->SetValueAsVector("PlayerPosition", TargetPlayer->GetActorLocation());

		FVector vectorLength = TargetPlayer->GetActorLocation() - GetPawn()->GetActorLocation();



		TArray <AActor*> FoundActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AA1Character::StaticClass(), FoundActors);
		target = Cast<AA1Character>(FoundActors[0]);

	
		TArray <AActor*> FoundActors2;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATimeBomb::StaticClass(), FoundActors2);


		for (int item = 0; item < FoundActors2.Num(); item++) {
			targetBomb = Cast<ATimeBomb>(FoundActors2[item]);
				if (targetBomb->explode==true && hasExplode ==false &&  BombdoOnce == false){
					//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("explode =true"));
						hasExplode = true;
						BombdoOnce = true;
						BombLocation = targetBomb->GetActorLocation(); 
				}
		}

		if (hasExplode && distractedOnce == false) {
			if (FVector::Dist(BombLocation, GetPawn()->GetActorLocation()) <= 4000) {
							BlackboardComponent->SetValueAsBool("CanDistract", true);
							GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Some Enemies hear the noise"));
							distractedOnce= true;
							beingDistracted = true;
							HeadToBomb();
			}
			else { distractedOnce = true; }
				
		}
		if (!hasExplode) { BlackboardComponent->ClearValue("CanDistract");}
				


		if (target->grenadeUsed == true && doOnce==false ) {
			if (FVector::Dist(TargetPlayer->GetActorLocation(), GetPawn()->GetActorLocation()) <= 1500) {


				BlackboardComponent->SetValueAsBool("CanStun", true);
				GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("Some Enemies got stun"));
				isStun = true;
				doOnce = true;
			}
			else {
				BlackboardComponent->ClearValue("CanStun");
				GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("No Enemy got stun"));
				doOnce = true;
			}

		}
		/*
		if (target->grenadeUsed == false ) {
			BlackboardComponent->ClearValue("CanStun");
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("grenad use is false"));
			
			doOnce = false;
			GenerateNewRandomLocation();
		}*/
		if (isStun) {
			if (target->grenadeUsed == false) { BlackboardComponent->ClearValue("CanStun"); 
			isStun = false;
			doOnce = false;
			GenerateNewRandomLocation();
			}
		}
		if (isStun == false) {
			BlackboardComponent->ClearValue("CanStun"); 
		}
		/*
		if (target->grenadeUsed == true) {
			BlackboardComponent->ClearValue("CanStun");
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("grenad use is true"));
			//doOnce = false;
		}*/

		if (FVector::Dist(TargetPlayer->GetActorLocation(), GetPawn()->GetActorLocation()) <= 110) {

			underAttack = true;
			target->EnemyAttack = true;
			if (underAttack) {
				/*
				TArray <AActor*> FoundActors;
				UGameplayStatics::GetAllActorsOfClass(GetWorld(), AA1Character::StaticClass(), FoundActors);
				target = Cast<AA1Character>(FoundActors[0]);*/
				if (target->invincibile == false) {
					target->healthDec(0.1);
					GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, TEXT("You are under attack"));
				}
				if (target->invincibile == true) {
					GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, TEXT("You are Invincible, Enemy made no damage on you!"));
				}

			}
		}
		if (FVector::Dist(TargetPlayer->GetActorLocation(), GetPawn()->GetActorLocation()) > 110) {
			underAttack = false;
			target->EnemyAttack = false;
		}

		if (beingDistracted) {
			if (FVector::Dist(BombLocation, GetPawn()->GetActorLocation()) <= 110) {


				BlackboardComponent->ClearValue("CanDistract");
				beingDistracted = false;
				hasExplode = false;

			}
		}

		if (BombdoOnce == true) {
			if (targetBomb->explode == false) {
				BombdoOnce = false;
			}
		}

	}


	/*

		if (FVector::Dist(TargetPlayer->GetActorLocation(), GetPawn()->GetActorLocation()) <= 1000) {

			
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Enemy can be stun"));

			TArray <AActor*> FoundActors;
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), AA1Character::StaticClass(), FoundActors);
			target = Cast<AA1Character>(FoundActors[0]);
			if (target->grenadeUsed == true) {
				BlackboardComponent->SetValueAsBool("IsStun", true);
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Enemy is stun"));
		}
			if (target->grenadeUsed == false) { BlackboardComponent->ClearValue("IsStun"); }

		}
		if (FVector::Dist(TargetPlayer->GetActorLocation(), GetPawn()->GetActorLocation()) > 1000){
			
		}*/

		

	//}
	
}

	
FRotator AEnemyAIController::GetControlRotation() const
{
	if (GetPawn()) {
		return FRotator(0, GetPawn()->GetActorRotation().Yaw, 0);
	}
	return FRotator(0, 0, 0);

}

void AEnemyAIController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{

}

void AEnemyAIController::OnSensesUpdated(AActor * UpdatedActor, FAIStimulus Stimulus)
{	




	APawn* TemporaryPawn = Cast<APawn>(UpdatedActor);
	if (TemporaryPawn&&TemporaryPawn->IsPlayerControlled()) {
		if (Stimulus.WasSuccessfullySensed()) {
			TargetPlayer = TemporaryPawn;
			BlackboardComponent->SetValueAsBool("ChasePlayer", true);
			BlackboardComponent->SetValueAsVector("PlayerPosition", TargetPlayer->GetActorLocation());
		}
		else {
			TargetPlayer = nullptr;
			BlackboardComponent->ClearValue("ChasePlayer");
		}
	}
	if (isStun) {
		if (target->grenadeUsed == false) {
			BlackboardComponent->ClearValue("CanStun");
			isStun = false;
			doOnce = false;
			GenerateNewRandomLocation();
		}
	}

}

void AEnemyAIController::GenerateNewRandomLocation()
{
	if (NavigationSystem) {
		
		FNavLocation returnLocation;
		NavigationSystem->GetRandomPointInNavigableRadius(GetPawn()->GetActorLocation(), 2000, returnLocation);
		BlackboardComponent->SetValueAsVector("PartolPoint", returnLocation.Location);
	
	}
}
void AEnemyAIController::GetPartolRoute()
{
	TArray <AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemyCharacter::StaticClass(), FoundActors);
	AEnemyCharacter* character = Cast<AEnemyCharacter>(FoundActors[0]);


}
void AEnemyAIController::HeadToBomb() {
	//BombLocation = targetBomb->GetActorLocation();
	if(beingDistracted==true){BlackboardComponent->SetValueAsVector("BombPosition", BombLocation);}
	
}