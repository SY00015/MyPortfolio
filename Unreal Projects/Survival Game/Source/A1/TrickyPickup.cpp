// Fill out your copyright notice in the Description page of Project Settings.


#include "TrickyPickup.h"

// Sets default values
ATrickyPickup::ATrickyPickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	BaseMesh->SetCollisionProfileName(TEXT("Trigger"));
	BaseMesh->SetupAttachment(RootComponent);



	//material
	OnMaterial = CreateDefaultSubobject<UMaterial>(TEXT("OnMaterial"));
	ConstructorHelpers::FObjectFinder<UStaticMesh>SphereVisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere"));
	ConstructorHelpers::FObjectFinder<UMaterial>OnMaterialObject(TEXT("/Game/Material/Red.Red"));

	OnMaterial2 = CreateDefaultSubobject<UMaterial>(TEXT("OnMaterial2"));
	ConstructorHelpers::FObjectFinder<UMaterial>OnMaterial2Object(TEXT("/Game/Material/Blue.Blue"));

	OnMaterial3 = CreateDefaultSubobject<UMaterial>(TEXT("OnMaterial3"));
	ConstructorHelpers::FObjectFinder<UMaterial>OnMaterial3Object(TEXT("/Game/Material/Green.Green"));



	if (OnMaterialObject.Succeeded())
	{
		OnMaterial = OnMaterialObject.Object;
	}
	if (OnMaterial2Object.Succeeded())
	{
		OnMaterial2 = OnMaterial2Object.Object;
	}

	if (OnMaterial3Object.Succeeded())
	{
		OnMaterial3 = OnMaterial3Object.Object;
	}


	if (SphereVisualAsset.Succeeded()) {
		BaseMesh->SetStaticMesh(SphereVisualAsset.Object);
	}
	//set random material
	x = rand() % 3;
	if (x == 0) {
		BaseMesh->SetMaterial(0, OnMaterialObject.Object);
	}

	if (x == 1) {
		BaseMesh->SetMaterial(0, OnMaterial2Object.Object);
	}

	if (x == 2) {
		BaseMesh->SetMaterial(0, OnMaterial3Object.Object);
	}

	LifeTime = 8;
}

// Called when the game starts or when spawned
void ATrickyPickup::BeginPlay()
{
	Super::BeginPlay();


}

// Called every frame
void ATrickyPickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	LifeTime -= DeltaTime;
	if (LifeTime <= 0) {
		ObjectDestory();
	}

}

void ATrickyPickup::Interact_Implementation()
{

	pickupTrickItem();
	//print message on screen 
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Ah Oh! You hit on a Trap!!"));

	ObjectDestory();

}
void ATrickyPickup::pickupTrickItem()
{	//increase food level in character by calling the foodInc function 
	TArray <AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AA1Character::StaticClass(), FoundActors);
	target = Cast<AA1Character>(FoundActors[0]);

	if (target->invincibile == false) {
	if (x == 0) { 
		target->healthDec(reduce); 
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, "10 Health Down! ");

	}
	if (x == 1) { 
		target->waterDec(reduce); 
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, "10 Water Down! ");
	}
	if (x == 2) {
		target->foodDec(reduce);
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, "10 Food Down! ");
	}
	}

}

void ATrickyPickup::ObjectDestory()
{	//destory self
	Destroy();

}
