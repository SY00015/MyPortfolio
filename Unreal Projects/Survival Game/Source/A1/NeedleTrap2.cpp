// Fill out your copyright notice in the Description page of Project Settings.


#include "NeedleTrap2.h"

// Sets default values
ANeedleTrap2::ANeedleTrap2()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	BaseMesh->SetCollisionProfileName(TEXT("Trigger"));
	BaseMesh->SetupAttachment(RootComponent);

	//material & visual asset
	//ConstructorHelpers::FObjectFinder<UStaticMesh>SphereVisualAsset(TEXT("/Game/ThirdPerson/StarterContent/Shapes/Shape_MyCone.Shape_MyCone"));
	ConstructorHelpers::FObjectFinder<UMaterial>OnMaterialObject(TEXT("/Game/Material/Red.Red"));

	//if (SphereVisualAsset.Succeeded()) {
	//	BaseMesh->SetStaticMesh(SphereVisualAsset.Object);
	//}
	if (OnMaterialObject.Succeeded()) {
		BaseMesh->SetMaterial(0, OnMaterialObject.Object);
	}


}

// Called when the game starts or when spawned
void ANeedleTrap2::BeginPlay()
{
	Super::BeginPlay();

	TArray <AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AA1Character::StaticClass(), FoundActors);
	target = Cast<AA1Character>(FoundActors[0]);

	StartingPosition = GetActorLocation();

	EndPosition = StartingPosition + (GetActorRightVector() * Direction * Distance);
}

// Called every frame
void ANeedleTrap2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector CurrentLocation = GetActorLocation();
	FVector DirectionVector = GetActorRightVector() * Direction;
	CurrentLocation += DirectionVector * Speed * DeltaTime;
	SetActorLocation(CurrentLocation);

	//check if the arrow reach the end position
	if (FVector::Dist(CurrentLocation, EndPosition) <= 10.f) {



		Destroy();
	}



}	


void ANeedleTrap2::Interact_Implementation()
{

	Hit();
	//print message on screen 
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("You hit on the Arrow"));
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, "10 Health Down! ");
	Destroy();

}

void ANeedleTrap2::Hit()
{	//decrease health in character
	if (target->invincibile == false) {target->healthDec(health);}
	

}
