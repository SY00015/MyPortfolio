// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/GameplayStatics.h"
#include "Interactable.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "A1Character.h"
#include "WaterPickup.generated.h"

UCLASS()
class A1_API AWaterPickup : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWaterPickup();
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Interact")
		class UStaticMeshComponent* BaseMesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void Interact();
	virtual void Interact_Implementation() override;

	//set water value
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Interact")
		float water = 20.0f;

	//destory self 
	void ObjectDestory();

	//water is picked up
	void pickupWater();

	//character pointer
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "target")
		AA1Character* target;

	//material
	UPROPERTY(EditAnywhere)
		UMaterial* OnMaterial;
};
