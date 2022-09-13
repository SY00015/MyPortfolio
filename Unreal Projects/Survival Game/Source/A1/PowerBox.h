// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Interactable.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "A1Character.h"
#include "Fuse.h"

#include "PowerBox.generated.h"

UCLASS()
class A1_API APowerBox : public AActor, public IInteractable

{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APowerBox();
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Interact")
		UStaticMeshComponent* VisibleComponent;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void Interact();
	virtual void Interact_Implementation() override;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "target")
		AA1Character* myCharacter;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		float FuseNumber;

		float HasFuseNumber;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Interact")
		bool HasFuse;

	UPROPERTY(EditAnywhere)
		UMaterial*OnMaterial;

	UPROPERTY(EditAnywhere)
		UMaterial* Material2;
};
