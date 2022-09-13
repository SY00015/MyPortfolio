// Fill out your copyright notice in the Description page of Project Settings.


#include "FoodPickup.h"

// Sets default values
AFoodPickup::AFoodPickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	BaseMesh->SetCollisionProfileName(TEXT("Trigger"));
	BaseMesh->SetupAttachment(RootComponent);

	//material
	ConstructorHelpers::FObjectFinder<UStaticMesh>SphereVisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere"));
	ConstructorHelpers::FObjectFinder<UMaterial>OnMaterialObject(TEXT("/Game/Material/Green.Green"));

	if (SphereVisualAsset.Succeeded()) {
		BaseMesh->SetStaticMesh(SphereVisualAsset.Object);
	}
	if (OnMaterialObject.Succeeded()) {
		BaseMesh->SetMaterial(0, OnMaterialObject.Object);
	}
}

// Called when the game starts or when spawned
void AFoodPickup::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFoodPickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFoodPickup::Interact_Implementation()
{

	pickupFood();
	//print message on screen 
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Picked Up Food Item"));
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, "20 Food UP! ");

	ObjectDestory();
	
}
void AFoodPickup::pickupFood() 
{	//increase food level in character by calling the foodInc function 
	TArray <AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AA1Character::StaticClass(), FoundActors);
	target = Cast<AA1Character>(FoundActors[0]);
	target->foodInc(food);

}

void AFoodPickup::ObjectDestory()
{	//destory self
	Destroy();
}

