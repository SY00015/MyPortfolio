// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Interactable.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "A1Character.h"
#include "MovableWall.generated.h"

UCLASS()
class A1_API AMovableWall : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMovableWall();
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Interact")
		UStaticMeshComponent* Wall;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interact")
		void Interact();
	virtual void Interact_Implementation() override;


	// the wall is turned 
	bool Turned;

	bool Touched;

	//the angle the wall will rotate to
	float TargetAngle = 90.f;

	//the angle of the wall 
	float RotateValue;


	//the direction of the wall movement, move the wall in clockwise
	int Direction = 1;

};
