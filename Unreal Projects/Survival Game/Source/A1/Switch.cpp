// Fill out your copyright notice in the Description page of Project Settings.


#include "Switch.h"

// Sets default values
ASwitch::ASwitch()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	VisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Visible Component"));
	VisibleComponent->SetupAttachment(RootComponent);


	ConstructorHelpers::FObjectFinder<UStaticMesh>SphereVisualAsset(TEXT("/Game/StarterContent/Architecture/Pillar_50x500.Pillar_50x500"));
	OnMaterial = CreateDefaultSubobject<UMaterial>(TEXT("OnMaterial"));
	ConstructorHelpers::FObjectFinder<UMaterial>OnMaterialObject(TEXT("/Game/FirstPerson/Meshes/BaseMaterial.BaseMaterial"));

	Material2 = CreateDefaultSubobject<UMaterial>(TEXT("Material2"));
	ConstructorHelpers::FObjectFinder<UMaterial>OnMaterial2Object(TEXT("/Game/StarterContent/Materials/M_Tech_Hex_Tile_Pulse.M_Tech_Hex_Tile_Pulse"));


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
	
	PitchValue=0.f;
	
	 YawValue=50.f;
	
	 RollValue=0.f;
}

// Called when the game starts or when spawned
void ASwitch::BeginPlay()
{
	Super::BeginPlay();
	TArray <AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASwitch::StaticClass(), FoundActors);
	if (MyKey!=NULL) {
	
				needKey = true;
				needFuse = false;
	}

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AFuse::StaticClass(), FoundActors);
	if (MyFuse!=NULL) {

		needFuse = true;
		needKey = false;
	}
	if(MyKey==NULL && MyFuse==NULL) { 
	needKey = false;
	needFuse = false;
	}


}
	

// Called every frame
void ASwitch::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!Unlock && turnOn) {
		FVector target = VisibleComponent->GetComponentLocation();

		FQuat QuatRotation = FQuat(FRotator(-45.f, 0, 0));
		//FRotator NewRotation = FRotator(PitchValue, YawValue, RollValue);

		//FQuat QuatRotation = FQuat(NewRotation);

		AddActorLocalRotation(QuatRotation, false, 0, ETeleportType::None);
		
		Unlock = true;
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("The Switch Is Unlock"));

		VisibleComponent->SetMaterial(0, Material2);
	}
	else {

	}
}
void ASwitch::Interact_Implementation()
{	
	if (needKey ==true && needFuse==false) {
	TArray <AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AA1Character::StaticClass(), FoundActors);
	myCharacter = Cast<AA1Character>(FoundActors[0]);
	for (AActor* actor : myCharacter->_inventory) {

		if (actor->IsA(AMyKey::StaticClass())) {
			if (actor->GetName() == MyKey->GetName()) {turnOn = !turnOn;}
			myCharacter->RemoveFromInventory(actor);
			myCharacter->holdingKey = false;
		}
	
		
	}

	if (!turnOn) { GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("You need a key")); }

	}
	if (needFuse == true && needKey == false) {
	
		TArray <AActor*> FoundActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), APowerBox::StaticClass(), FoundActors);
		myPowerBox = Cast<APowerBox>(FoundActors[0]);
		if (myPowerBox->HasFuse) {
			turnOn = !turnOn;

		}
		if (!turnOn) { GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("The Power Box has not activated yet")); }
			
		}
		

	if(!needKey && !needFuse) {
		
			turnOn = !turnOn;
		
			if (turnOn==false) {
				Unlock = false;
				FVector target = VisibleComponent->GetComponentLocation();

				FQuat QuatRotation = FQuat(FRotator(+45.f, 0, 0));


				AddActorLocalRotation(QuatRotation, false, 0, ETeleportType::None);

				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("The Switch Is Lock"));
				VisibleComponent->SetMaterial(0, OnMaterial);
			}
	
	}
	if (Unlock) {
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("The Switch Is Already Activated"));

	}
}
