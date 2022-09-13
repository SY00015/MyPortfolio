// Fill out your copyright notice in the Description page of Project Settings.


#include "WaterPickup.h"

// Sets default values
AWaterPickup::AWaterPickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.

	PrimaryActorTick.bCanEverTick = true;
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	BaseMesh->SetCollisionProfileName(TEXT("Trigger"));
	BaseMesh->SetupAttachment(RootComponent);

	//material
	ConstructorHelpers::FObjectFinder<UStaticMesh>SphereVisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere"));
	ConstructorHelpers::FObjectFinder<UMaterial>OnMaterialObject(TEXT("/Game/Material/Blue.Blue"));

	if (SphereVisualAsset.Succeeded()) {
		BaseMesh->SetStaticMesh(SphereVisualAsset.Object);
	}
	if (OnMaterialObject.Succeeded()) {
		BaseMesh->SetMaterial(0, OnMaterialObject.Object);
	}

}

// Called when the game starts or when spawned
void AWaterPickup::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWaterPickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void AWaterPickup::Interact_Implementation()
{
	pickupWater();
	//print message on screen
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Picked Up Water Item"));
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, "20 Water UP! ");
	ObjectDestory();

}
void AWaterPickup::ObjectDestory()
{	//destory self after being pickup
	Destroy();
}

void AWaterPickup::pickupWater()
{
	//increase water level in character by calling the waterInc function 
	TArray <AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AA1Character::StaticClass(), FoundActors);
	target = Cast<AA1Character>(FoundActors[0]);
	target->waterInc(water);
}


