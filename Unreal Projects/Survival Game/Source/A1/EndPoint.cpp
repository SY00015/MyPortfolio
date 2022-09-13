// Fill out your copyright notice in the Description page of Project Settings.
#include "EndPoint.h"
#include "Components/StaticMeshComponent.h"
#include"UObject/ConstructorHelpers.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"
#include "A1Character.h"


// Sets default values
AEndPoint::AEndPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	BaseMesh->SetCollisionProfileName(TEXT("Trigger"));
	BaseMesh->SetupAttachment(RootComponent);

	ConstructorHelpers::FObjectFinder<UStaticMesh>SphereVisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_Cone.Shape_Cone"));
	

	if (SphereVisualAsset.Succeeded()) {
		BaseMesh->SetStaticMesh(SphereVisualAsset.Object);
	}





}

// Called when the game starts or when spawned
void AEndPoint::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEndPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEndPoint::Interact_Implementation()
{
	// player win the game
	TArray <AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AA1Character::StaticClass(), FoundActors);
	target = Cast<AA1Character>(FoundActors[0]);
	target->checkWon();



}
