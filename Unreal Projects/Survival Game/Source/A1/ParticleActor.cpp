// Fill out your copyright notice in the Description page of Project Settings.


#include "ParticleActor.h"

// Sets default values
AParticleActor::AParticleActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AParticleActor::BeginPlay()
{
	Super::BeginPlay();
	
	/*
	MyCoolFX = LoadObject<UNiagaraSystem>(nullptr, TEXT("NiagaraSystem'/Game/NiagaraFX/SpriteEffect/SmokeSystem.SmokeSystem'"), nullptr, LOAD_None, nullptr);

	UNiagaraComponent * effect = UNiagaraFunctionLibrary::SpawnSystemAtLocation(
	GetWorld(),
		MyCoolFX,
		FVector(100,100,200),
		FRotator(1),
		FVector(0.05,0.05,0.05),
		true,
		true,
		ENCPoolMethod::AutoRelease,
		true
		);*/
}//NiagaraSystem'/Game/NiagaraFX/SpriteEffect/SmokeSystem.SmokeSystem'

// Called every frame
void AParticleActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

