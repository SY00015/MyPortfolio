// Fill out your copyright notice in the Description page of Project Settings.


#include "Fuse.h"

// Sets default values
AFuse::AFuse()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MyMesh"));
	RootComponent = MyMesh;
}

// Called when the game starts or when spawned
void AFuse::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFuse::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFuse::Interact_Implementation()
{
	pickup();
	
}

void AFuse::pickup()
{
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("You Picked Up a Key"));
	TArray <AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AA1Character::StaticClass(), FoundActors);
	myCharacter = Cast<AA1Character>(FoundActors[0]);

	if (myCharacter) {
		myCharacter->AddToInventory(this);
		myCharacter->holdingFuse=true;

		//destory self
		Destroy();
	}

}


