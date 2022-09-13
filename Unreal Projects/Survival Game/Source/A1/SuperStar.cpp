// Fill out your copyright notice in the Description page of Project Settings.


#include "SuperStar.h"

// Sets default values
ASuperStar::ASuperStar()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	BaseMesh->SetCollisionProfileName(TEXT("Trigger"));
	BaseMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ASuperStar::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASuperStar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASuperStar::Interact_Implementation()


{	
	pickupItem();
	//print message on screen 
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Picked Up Super Star"));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, "You are now temporary invincibile! (6s)");
}

void ASuperStar::pickupItem()
{
	TArray <AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AA1Character::StaticClass(), FoundActors);
	target = Cast<AA1Character>(FoundActors[0]);
	target->invincibile = true;
	Destroy();


}

