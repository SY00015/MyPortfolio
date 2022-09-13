// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerBox.h"

// Sets default values
APowerBox::APowerBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	VisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Visible Component"));
	VisibleComponent->SetupAttachment(RootComponent);


	ConstructorHelpers::FObjectFinder<UStaticMesh>SphereVisualAsset(TEXT("/Game/Geometry/Meshes/1M_Cube.1M_Cube"));
	
	OnMaterial = CreateDefaultSubobject<UMaterial>(TEXT("OnMaterial"));
	ConstructorHelpers::FObjectFinder<UMaterial>OnMaterialObject(TEXT("/Game/FirstPerson/Meshes/BaseMaterial.BaseMaterial"));

	Material2 = CreateDefaultSubobject<UMaterial>(TEXT("Material2"));
	ConstructorHelpers::FObjectFinder<UMaterial>OnMaterial2Object(TEXT("/Game/Material/Green_PowerBox.Green_PowerBox"));

	
	if (SphereVisualAsset.Succeeded()) {
		VisibleComponent->SetStaticMesh(SphereVisualAsset.Object);
	}

	if (OnMaterialObject.Succeeded())
	{
		OnMaterial = OnMaterialObject.Object;
	}
	if (OnMaterialObject.Succeeded())
	{
		Material2 = OnMaterial2Object.Object;
	}

	VisibleComponent->SetMaterial(0, OnMaterial);
	HasFuse = false;
	FuseNumber = 3;
}

// Called when the game starts or when spawned
void APowerBox::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APowerBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APowerBox::Interact_Implementation()
{
	TArray <AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AA1Character::StaticClass(), FoundActors);
	myCharacter = Cast<AA1Character>(FoundActors[0]);
	for (AActor* actor : myCharacter->_inventory) {

		if (actor->IsA(AFuse::StaticClass())) {
			HasFuseNumber += 1;


		}
		
		if (HasFuseNumber == FuseNumber) {
			HasFuse = true;
			VisibleComponent->SetMaterial(0, Material2);
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Power Box activated! "));
			for (AActor* item : myCharacter->_inventory) {

				if (item->IsA(AFuse::StaticClass())) {
					myCharacter->RemoveFromInventory(item);
				}


			}	myCharacter->holdingFuse = false;
		}
		if (!HasFuse) {
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("You don't have enough Fuse"));
		}
	}
}

