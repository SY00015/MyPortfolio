// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/GameplayStatics.h"
#include "Interactable.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "A1Character.h"
#include "Math/UnrealMathUtility.h"
#include "TrickyPickup.generated.h"

UCLASS()
class A1_API ATrickyPickup : public AActor, public IInteractable

{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATrickyPickup();
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


	//set food value
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Interact")
		float reduce = 10.0f;



	//random number
	int x;

	//destory self 
	void ObjectDestory();

	//Item is picked up
	void pickupTrickItem();

	//Life timw of the actor
	float LifeTime;

	//character pointer
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "target")
		AA1Character* target;

	//material
	UPROPERTY(EditAnywhere)
		UMaterial* OnMaterial;

	UPROPERTY(EditAnywhere)
		UMaterial* OnMaterial2;

	UPROPERTY(EditAnywhere)
		UMaterial* OnMaterial3;

};
