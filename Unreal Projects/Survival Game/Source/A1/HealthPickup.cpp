// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthPickup.h"


// Sets default values
AHealthPickup::AHealthPickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	BaseMesh->SetCollisionProfileName(TEXT("Trigger"));
	//RootComponent = BaseMesh;
	BaseMesh->SetupAttachment(RootComponent);

	//material
	ConstructorHelpers::FObjectFinder<UStaticMesh>SphereVisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere"));
	ConstructorHelpers::FObjectFinder<UMaterial>OnMaterialObject(TEXT("/Game/Material/Red.Red"));

	if (SphereVisualAsset.Succeeded()) {
		BaseMesh->SetStaticMesh(SphereVisualAsset.Object);
	}
	if (OnMaterialObject.Succeeded()) {
		BaseMesh->SetMaterial(0, OnMaterialObject.Object);
	}

}

// Called when the game starts or when spawned
void AHealthPickup::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHealthPickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHealthPickup::Interact_Implementation()
{
	
	pickupHealth();
	//print message on screen
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Picked Up Health Item"));
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, "20 Health UP! ");
	ObjectDestory();

}

void AHealthPickup::ObjectDestory()
{	//destroy self after being pickup
	Destroy();
}

void AHealthPickup::pickupHealth()
{
	//increase health level in character by calling the healthInc function 
	TArray <AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AA1Character::StaticClass(), FoundActors);
	target = Cast<AA1Character>(FoundActors[0]);
	target->healthInc(health);
}

