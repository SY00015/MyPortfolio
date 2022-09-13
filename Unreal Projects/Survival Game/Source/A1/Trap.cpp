// Fill out your copyright notice in the Description page of Project Settings.


#include "Trap.h"

// Sets default values
ATrap::ATrap()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	BaseMesh->SetCollisionProfileName(TEXT("Trigger"));
	BaseMesh->SetupAttachment(RootComponent);

	ConstructorHelpers::FObjectFinder<UStaticMesh>SphereVisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_Cone.Shape_Cone"));
	ConstructorHelpers::FObjectFinder<UMaterial>OnMaterialObject(TEXT("/Game/Material/Red.Red"));

	if (SphereVisualAsset.Succeeded()) {
		BaseMesh->SetStaticMesh(SphereVisualAsset.Object);
	}
	if (OnMaterialObject.Succeeded()) {
		BaseMesh->SetMaterial(0, OnMaterialObject.Object);
	}

}

// Called when the game starts or when spawned
void ATrap::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATrap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATrap::Interact_Implementation()
{

	TArray <AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AA1Character::StaticClass(), FoundActors);
	target = Cast<AA1Character>(FoundActors[0]);
	target->healthDec(health);

	//print message on screen 
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("You fell onto the trap"));
	

	

}