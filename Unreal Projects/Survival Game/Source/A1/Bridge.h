// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Interactable.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Switch.h"
#include "A1Character.h"
#include "Kismet/GameplayStatics.h"
#include "Bridge.generated.h"

UCLASS()
class A1_API ABridge : public AActor

{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABridge();

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* VisibleComponent;

	//if bridge shown
	//bool showBridge;
	float baseY = 0;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	//virtual void show(bool visible);
	//virtual void acitivated(bool visible);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
		UMaterial*OnMaterial;

	UPROPERTY(EditAnywhere)
		UMaterial* Material2;

	/**/
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "target")
		ASwitch* target;


	UPROPERTY(EditAnywhere)
		AActor* MyTarget;

};
