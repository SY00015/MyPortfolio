// Fill out your copyright notice in the Description page of Project Settings.


#include "TimeBomb.h"

// Sets default values
ATimeBomb::ATimeBomb()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MyMesh"));
	RootComponent = MyMesh;

}

// Called when the game starts or when spawned
void ATimeBomb::BeginPlay()
{

	Super::BeginPlay();
	doCountDown = false;
	countDown = 8;
	placed = false;
	explode = false;
	spawnSmoke = false;
	destroyCountDown = 5;
}

// Called every frame
void ATimeBomb::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	TArray <AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AA1Character::StaticClass(), FoundActors);
	target = Cast<AA1Character>(FoundActors[0]);
	if (target->bombUsed== true && placed==false) {
		//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("placebomb =true "));
		itemUsed();

		doCountDown = true;
		placed = true;
		target->bombUsed = false;

	}
	if (placed) {
		this->MyMesh->SetVisibility(true);
	}
	if (doCountDown) {
		//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("do count down "));
		if (countDown > 0) {
			countDown -= 0.1;
			//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("count -1 ;"));
		}
		
		if (countDown <= 0) { 
			//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("count=0 "));
			Explosion();
			doCountDown = false;
			countDown = 8;
		}
	}
		if (explode==true) {
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("exlode"));
			if (destroyCountDown > 0) {
				destroyCountDown -= 0.03;
				//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("Bomb counting down"));
			}
			if (destroyCountDown <= 0) { 
				
				spawnSmoke = false;
				//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Bomb destroied"));
				Destroy(); 
				explode = false;
				destroyCountDown = 5;
			}
		}
		/*
		if (explode == false) {
			GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("Not exlode"));
			
		}
*/
}

void ATimeBomb::Interact_Implementation()
{
	pickupItem();
	
}

void ATimeBomb::pickupItem()
{
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("You Picked Up a Time Bomb"));
	TArray <AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AA1Character::StaticClass(), FoundActors);
	target = Cast<AA1Character>(FoundActors[0]);


	if (target) {

		target->AddToInventory(this);
		target->holdingBomb = true;
		if (placed == false) {
			
			this->MyMesh->SetVisibility(false);
			//this->MyMesh->SetCollisionEnabled(false?);
		}
		
	}
	//IsHidden();


	
}


void ATimeBomb::itemUsed() {

	
	FVector CurrentLocation;
	CurrentLocation = target->GetActorLocation(); // To save where ever the actor is in the viewport
	SetActorLocation(CurrentLocation);
	


}

void ATimeBomb::Explosion()
{	

	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("Bomb! "));
	explode = true;
	spawnSmoke = true;
	//Destroy();
	placed = false;
	show(false);

	//this->MyMesh->SetVisibility(false);
}

void ATimeBomb::show(bool visible) {
	ECollisionEnabled::Type collision = visible ?
		ECollisionEnabled::QueryAndPhysics :
		ECollisionEnabled::NoCollision;

	//this->SetActorTickEnabled(visible);

	this->MyMesh->SetVisibility(visible);
	this->MyMesh->SetCollisionEnabled(collision);
	
	//this->BoxCollider->SetCollisionEnabled(collision);


}