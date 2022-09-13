// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Interactable.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "A1Character.h"

#include "PowerBox.h"
#include "MyKey.h"
#include "Switch.generated.h"
class A1Character;

UCLASS()
class A1_API ASwitch : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASwitch();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Interact")
		UStaticMeshComponent* VisibleComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Interact")
		bool turnOn = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Interact")
		bool Unlock = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		bool needKey;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		bool needFuse;


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Interact")
		bool HasFuse;


	UPROPERTY(EditAnywhere, Category = "Movement")
		float PitchValue;
	UPROPERTY(EditAnywhere, Category = "Movement")
		float YawValue;
	UPROPERTY(EditAnywhere, Category = "Movement")
		float RollValue;
	//float Rotate = 150.0f;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interact")
		void Interact();
	virtual void Interact_Implementation() override;

	//materials

	UPROPERTY(EditAnywhere)
		UMaterial*OnMaterial;

	UPROPERTY(EditAnywhere)
		UMaterial* Material2;

	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "target")
		AA1Character* myCharacter;

		APowerBox* myPowerBox;

	UPROPERTY(EditAnywhere)
		AActor* MyKey;


	//Need a Fuse
	UPROPERTY(EditAnywhere)
		AActor* MyFuse;	

	bool binary;

	
};
