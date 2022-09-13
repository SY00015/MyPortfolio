// Fill out your copyright notice in the Description page of Project Settings.


#include "Bridge.h"
#include "Kismet/GameplayStatics.h"
// Sets default values
ABridge::ABridge()
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
	//bridge is hidden 
	//showBridge = true;
}

// Called when the game starts or when spawned
void ABridge::BeginPlay()
{
	Super::BeginPlay();
	//look for the switch

	/*
	TArray <AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASwitch::StaticClass(), FoundActors);
	if (MyTarget) {
		TArray<ASwitch*> mySwitch;
		for (const auto& actor : FoundActors) {
			if (actor->GetName() == MyTarget->GetName()) {
				mySwitch.Add( Cast <ASwitch>(actor));
				target = mySwitch[0];

			}


		}
	}*/
	//show(showBridge);
	//if (showBridge) {
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("The bridge should be shown"));



	//}


	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("The bridge is activated"));
	FVector self = VisibleComponent->GetComponentLocation();
	self.Y = baseY - 90.0f;
	VisibleComponent->SetRelativeLocation(FMath::Lerp(VisibleComponent->GetComponentLocation(), self, 0.05f));
	VisibleComponent->SetMaterial(0, Material2);
}

// Called every frame
void ABridge::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//show(showBridge);
	//check if the target switch is unlcok

	/*
	if (target->Unlock==true) {

		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("The bridge is activated"));
		FVector self = VisibleComponent->GetComponentLocation();
		self.Y = baseY - 90.0f;
		VisibleComponent->SetRelativeLocation(FMath::Lerp(VisibleComponent->GetComponentLocation(), self, 0.05f));
		VisibleComponent->SetMaterial(0, Material2);
		//show bridge
		//showBridge = true;
	}
	else {
		FVector self = VisibleComponent->GetComponentLocation();
		self.Y = baseY ;
		VisibleComponent->SetRelativeLocation(FMath::Lerp(VisibleComponent->GetComponentLocation(), self, 0.05f));
	}*/
	//show(showBridge);
}

/*
	
void ABridge::show(bool visible) {
	ECollisionEnabled::Type collision = visible ?
		ECollisionEnabled::QueryAndPhysics :
		ECollisionEnabled::NoCollision;



	this->VisibleComponent->SetVisibility(visible);
	this->VisibleComponent->SetCollisionEnabled(collision);

}*/
