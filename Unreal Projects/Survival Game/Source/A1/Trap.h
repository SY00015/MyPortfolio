// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "A1Character.h"
#include "Trap.generated.h"

UCLASS()
class A1_API ATrap : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATrap();
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



	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* MyMesh;



	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "target")
		AA1Character* target;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Interact")
		float health = 100.0f;

};
