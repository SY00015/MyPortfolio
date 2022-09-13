// Fill out your copyright notice in the Description page of Project Settings.


#include "MyDoor.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AMyDoor::AMyDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	RootComponent = BaseMesh;
	BaseMesh->SetRelativeLocation(FVector(0.f, 0.f, 0.f));

}

// Called when the game starts or when spawned
void AMyDoor::BeginPlay()
{
	Super::BeginPlay();

	//SetActorLocationAndRotation(NewLocation, NewRotation, false, 0, ETeleportType::None);


	//get the start position of the door
	StartingPosition = GetActorLocation();

	EndPosition = StartingPosition + (GetActorRightVector() * Direction * Distance);

	//The switch the door is looking at 
	TArray <AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASwitch::StaticClass(), FoundActors);
	if (MyTarget) {
		TArray<ASwitch*> mySwitch;
		for (const auto& actor : FoundActors) {
			if (actor->GetName() == MyTarget->GetName()) {
				mySwitch.Add(Cast <ASwitch>(actor));
				target = mySwitch[0];

			}


		}
	}
	// the door is not open 
	isOpened = false;

	//the position of the door is fixed once opened
	doOnce = true;

}

// Called every frame
void AMyDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


		//Check if the door has a look at switch
	if (MyTarget != NULL) {
		//if the door is not yet opened

		//if the look at switch is unlocked, open the door
		if (target->Unlock == true && isOpened == false) {

			//move the door to left
			FVector CurrentLocation = GetActorLocation();
			FVector DirectionVector = GetActorRightVector() * Direction;
			CurrentLocation += DirectionVector * Speed * DeltaTime;
			SetActorLocation(CurrentLocation);
			//check if the door reach the end position
			if (FVector::Dist(CurrentLocation, EndPosition) <= 10.f) {
				isOpened = true;
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("The Door is Opened"));
			}

		}
	}
	else {
		//check if the binary code is corrected
		if (isBC) {
			if (!isOpened) {
				//move the door to left
				FVector CurrentLocation = GetActorLocation();
				FVector DirectionVector = GetActorRightVector() * Direction;
				CurrentLocation += DirectionVector * Speed * DeltaTime;
				SetActorLocation(CurrentLocation);

				//check if the door reach the end position
				if (FVector::Dist(CurrentLocation, EndPosition) <= 10.f) {
					isOpened = true;
					GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("The Door is Opened"));
				}

			}

		}

		if (!isBC) {
			if (isOpened) {
				//move the door to left
				FVector CurrentLocation = GetActorLocation();
				FVector DirectionVector = GetActorRightVector() * Direction;
				CurrentLocation -= DirectionVector * Speed * DeltaTime;
				SetActorLocation(CurrentLocation);
				//check if the door reach the end position
				if (FVector::Dist(CurrentLocation, EndPosition) <= 10.f) {
					isOpened = false;
					GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("The Door is Locked"));
				}
			}
			
		}
	}
	
}

