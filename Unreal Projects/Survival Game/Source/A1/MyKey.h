// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "MyKey.generated.h"

class AA1Character;
UCLASS()

class A1_API AMyKey : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyKey();
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

	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Interact")
		//bool getMyKey;


		
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* MyMesh;
	UFUNCTION()
		void pickup();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "target")
		AA1Character* myCharacter;
	virtual void show(bool visible) ;
	
};
