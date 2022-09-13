// Fill out your copyright notice in the Description page of Project Settings.


#include "NewBridge.h"

// Sets default values
ANewBridge::ANewBridge()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	VisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Visible Component"));
	VisibleComponent->SetupAttachment(RootComponent);

	OnMaterial = CreateDefaultSubobject<UMaterial>(TEXT("OnMaterial"));
	ConstructorHelpers::FObjectFinder<UStaticMesh>SphereVisualAsset(TEXT("/Game/StarterContent/Architecture/Floor_400x400.Floor_400x400"));
	ConstructorHelpers::FObjectFinder<UMaterial>OnMaterialObject(TEXT("/Game/Material/Bridge.Bridge"));

	Material2 = CreateDefaultSubobject<UMaterial>(TEXT("Material2"));
	ConstructorHelpers::FObjectFinder<UMaterial>OnMaterial2Object(TEXT("/Game/Material/Bridge_Glow.Bridge_Glow"));


	if (SphereVisualAsset.Succeeded()) {
		VisibleComponent->SetStaticMesh(SphereVisualAsset.Object);
	}

	if (OnMaterialObject.Succeeded())
	{
		OnMaterial = OnMaterialObject.Object;
	}
	if (OnMaterialObject.Succeeded())
	{
		Material2 = OnMaterial2Object.Object;
	}

	VisibleComponent->SetMaterial(0, OnMaterial);
	doOnce = true;
	angle = -90.f;
}

// Called when the game starts or when spawned
void ANewBridge::BeginPlay()
{
	Super::BeginPlay();
	
	TArray <AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASwitch::StaticClass(), FoundActors);
	if (MyTarget) {
		TArray<ASwitch*> mySwitch;
		for (const auto& actor : FoundActors) {
			if (actor->GetName() == MyTarget->GetName()) {
				mySwitch.Add(Cast <ASwitch>(actor));
				target = mySwitch[0];

			}

			
		}
	}

}
// Called every frame
void ANewBridge::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	//put down the bridge

	if (MyTarget != NULL) {
		if (target->Unlock == true && doOnce) {
			angle += 1.f;
			if (angle < 0.f) {
				FQuat QuatRotation = FQuat(FRotator(-1.f, 0, 0));
				AddActorLocalRotation(QuatRotation, false, 0, ETeleportType::None);


			}
			//stop 
			else {
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("The bridge is activated"));
				doOnce = false;
			}

			VisibleComponent->SetMaterial(0, Material2);

		}
		else {

		}
	}
	else {
		// check the binary code is correct or not
		if (isBC) {
	
			BCPutDownBridge(); }

		if (!isBC) {

			BCLiftBridge();
		}
	}
}

void ANewBridge::BCPutDownBridge()
{	
	angle += 1.f;
	if (doOnce) {
	if (angle < 0.f) {
		FQuat QuatRotation = FQuat(FRotator(-1.f, 0, 0));
		AddActorLocalRotation(QuatRotation, false, 0, ETeleportType::None);
		
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("The bridge is activated"));
		
		doOnce = false;
	}
	//bridge glow
	VisibleComponent->SetMaterial(0, Material2);
	}
}

void ANewBridge::BCLiftBridge()
{

	if (!doOnce){
	FQuat QuatRotation = FQuat(FRotator(-90*-1.f, 0, 0));
	


	AddActorWorldRotation(QuatRotation, false, 0, ETeleportType::None);



	angle = -90.f;
	doOnce = true;
	}

	//bridge show not glow
	VisibleComponent->SetMaterial(0, OnMaterial);

}