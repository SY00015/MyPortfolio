// Fill out your copyright notice in the Description page of Project Settings.


#include "MovableWall.h"

// Sets default values
AMovableWall::AMovableWall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	Wall = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wall"));
	Wall->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AMovableWall::BeginPlay()
{
	Super::BeginPlay();

	//Player not yet touch the wall
	Touched = false;

	//The wall has not been turned yet
	Turned = false;

	//The Roatation of the Wall is zero
	RotateValue = 0.f;
}

// Called every frame
void AMovableWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Call the function when the player interact with the wall 
	if (Touched) { 
		//Check if the wall has been turned
		if (!Turned) {
			//create movement of the wall
			RotateValue += 1.f;
			if (RotateValue < TargetAngle) {
			FQuat QuatRotation = (FQuat(FRotator(0.f, 0.f, -1.f)));
			AddActorLocalRotation(QuatRotation, false, nullptr, ETeleportType::None);

			
			}
			//when finished rotating the wall
			else {
				Turned = true;
				Touched = false;
				RotateValue = 0.f;
			}

		}
		//The wall has not been turned
		else {
			//create movement of the wall, rotate the wall back to the original position
			RotateValue += 1.f;
			if (RotateValue < TargetAngle) {
			FQuat QuatRotation = FQuat(FRotator(0.f, 0.f, 1.f));
			AddActorLocalRotation(QuatRotation, false, nullptr, ETeleportType::None);
			}
			//rotation finished 
			else {
				Turned = false;
				Touched = false;
				RotateValue = 0.f;
			}
			

		}

	}
		
	

}

void AMovableWall::Interact_Implementation() {

	Touched = true;

}