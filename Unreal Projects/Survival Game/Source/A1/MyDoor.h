// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Switch.h"
#include "MyDoor.generated.h"

UCLASS()
class A1_API AMyDoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyDoor();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Interact")
		class UStaticMeshComponent* BaseMesh;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//the door is triggered to open 
	bool isTriggered;

	// the door is opened 
	bool isOpened;

	//the speed of the door movement 
	float Speed = 150.0f;

	//the distance of the door movement 
	float Distance = 500.f;

	//the direction of the door movement, move the door to left
	int Direction = -1;

	//Once the door is opened then fix the position 
	bool doOnce;


	//
	bool Done;

	//where the door start to move
	FVector StartingPosition;     

	//where the door stop moveing
	FVector EndPosition;         



	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "target")
		ASwitch* target;


	UPROPERTY(EditAnywhere)
		AActor* MyTarget;

	//binary code is correct
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "target")
		bool isBC;



};
