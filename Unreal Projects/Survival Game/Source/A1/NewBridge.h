// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Switch.h"
#include "NewBridge.generated.h"

UCLASS()
class A1_API ANewBridge : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANewBridge();
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* VisibleComponent;

	float baseY = 0;
	bool doOnce;
	float angle;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void BCPutDownBridge();

	UFUNCTION(BlueprintCallable)
		void BCLiftBridge();

	UPROPERTY(EditAnywhere)
		UMaterial*OnMaterial;

	UPROPERTY(EditAnywhere)
		UMaterial* Material2;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "target")
		ASwitch* target;


	UPROPERTY(EditAnywhere)
		AActor* MyTarget;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "target")
		bool isBC;

	bool done;
};
