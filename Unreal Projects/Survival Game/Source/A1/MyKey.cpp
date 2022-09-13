// Fill out your copyright notice in the Description page of Project Settings.

#include "MyKey.h"
#include "A1Character.h"

// Sets default values
AMyKey::AMyKey()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MyMesh"));
	RootComponent = MyMesh;


	ConstructorHelpers::FObjectFinder<UStaticMesh>SphereVisualAsset(TEXT("/Game/Mesh/MyKey.MyKey"));
	//ConstructorHelpers::FObjectFinder<UMaterial>OnMaterialObject(TEXT("/Game/Material/M_Metal_Gold.M_Metal_Gold")); 

	if (SphereVisualAsset.Succeeded()) {
		MyMesh->SetStaticMesh(SphereVisualAsset.Object);
	}
	/*
	if (OnMaterialObject.Succeeded()) {
		MyMesh->SetMaterial(0, OnMaterialObject.Object);
	}*/

}

// Called when the game starts or when spawned
void AMyKey::BeginPlay()
{
	Super::BeginPlay();
	

}

// Called every frame
void AMyKey::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

void AMyKey::Interact_Implementation()
{
	pickup();
}

void AMyKey::pickup()
{	

	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("You Picked Up a Key"));
	TArray <AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AA1Character::StaticClass(), FoundActors);
	myCharacter = Cast<AA1Character>(FoundActors[0]);
	
	
	if (myCharacter) {
		show(false);
		myCharacter->AddToInventory(this);
		myCharacter->holdingKey = true;
	
	}
	
}
void AMyKey::show(bool visible) {
	ECollisionEnabled::Type collision = visible ?
		ECollisionEnabled::QueryAndPhysics :
		ECollisionEnabled::NoCollision;

	this->SetActorTickEnabled(visible);

	this->MyMesh->SetVisibility(visible);
	this->MyMesh->SetCollisionEnabled(collision);
	//this->BoxCollider->SetCollisionEnabled(collision);


}
