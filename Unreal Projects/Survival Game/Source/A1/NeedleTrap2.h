// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "Kismet/GameplayStatics.h"
#include "Interactable.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "A1Character.h"
#include "NeedleTrap2.generated.h"

UCLASS()
class A1_API ANeedleTrap2 : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANeedleTrap2();
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

	void Hit();


	float health = 10;
	//character pointer
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "target")
		AA1Character* target;

	//material
	UPROPERTY(EditAnywhere)
		UMaterial* OnMaterial;

	//where the Arrow start to move
	FVector StartingPosition;


	//where the Arrow finish movement 
	FVector EndPosition;

	//the speed of the Arrow movement 
	float Speed = 500.f;

	//the distance of the Arrow movement 
	float Distance = 3000.f;

	//the direction of the Arrow movement, move the Arrow from left to right
	int Direction = -1;

	FVector MyString;
};
