// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/GameplayStatics.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"
#include "A1Character.h"
#include "TimeBomb.generated.h"

UCLASS()
class A1_API ATimeBomb : public AActor, public IInteractable
{
	GENERATED_BODY()

	
public:	
	// Sets default values for this actor's properties
	ATimeBomb();
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
	void pickupItem();

	void itemUsed();

	void Explosion();

	float countDown;

	float destroyCountDown;

	bool doCountDown;

	bool placed;
	
	bool explode;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		bool spawnSmoke;

	//character pointer
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "target")
		class AA1Character* target;

	//material
	UPROPERTY(EditAnywhere)
		UMaterial* OnMaterial;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* MyMesh;

	virtual void show(bool visible);

};
