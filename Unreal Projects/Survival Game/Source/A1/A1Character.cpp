// Copyright Epic Games, Inc. All Rights Reserved.

#include "A1Character.h"
#include "HealthPickup.h"
#include "MyKey.h"
#include "Switch.h"
#include "Fuse.h"
#include "EnemyCharacter.h"
#include "Interactable.h"
#include "A1Projectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/InputSettings.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include"GameFramework/CharacterMovementComponent.h"
#include "MotionControllerComponent.h"
#include "XRMotionControllerBase.h" // for FXRMotionControllerBase::RightHandSourceId

DEFINE_LOG_CATEGORY_STATIC(LogFPChar, Warning, All);

//////////////////////////////////////////////////////////////////////////
// AA1Character

AA1Character::AA1Character()
{	
	//attributes
	health = 100;
	water = 100;
	food = 100;

	//timer
	SpaenInterval = 1;
	countDown = 0;
	StartTime = 1;
	//player status 
	playing = false;
	pause =false;
	dead = false;
	won = false;

	CanPickup = false;

	//check if holding item 
	holdingKey = false;
	holdingFuse = false;

	//grenade variables
	holdingGrenade = false;
	grenadeUsed = false;
	GrenadeCountDown = 6;

	//invincible ability 
	invincibile = false;
	invincibileCountDown = 6;

	//bomb variables 
	bombUsed = false;
	holdingBomb = false;

	//player walk speed
	WalkSpeed = GetCharacterMovement()->MaxWalkSpeed *0.9;
	MaxSpeed = GetCharacterMovement()->MaxWalkSpeed;

	blurredVision = false;
	EnemyAttack = false;


	 spawnExplode=false;

	//trigger
	TriggerCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Trigger Capsule"));
	TriggerCapsule->InitCapsuleSize(55.0f, 96.0f);
	TriggerCapsule->SetCollisionProfileName(TEXT("Trigger"));
	TriggerCapsule->SetupAttachment(RootComponent);

	TriggerCapsule->OnComponentBeginOverlap.AddDynamic(this, &AA1Character::OnOverlapBegin);
	TriggerCapsule->OnComponentEndOverlap.AddDynamic(this, &AA1Character::OnOverlapEnd);

	// 
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-39.56f, 1.75f, 64.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->SetRelativeRotation(FRotator(1.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-0.5f, -4.4f, -155.7f));

	// Create a gun mesh component
	FP_Gun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FP_Gun"));
	FP_Gun->SetOnlyOwnerSee(true);			// only the owning player will see this mesh
	FP_Gun->bCastDynamicShadow = false;
	FP_Gun->CastShadow = false;
	// FP_Gun->SetupAttachment(Mesh1P, TEXT("GripPoint"));
	FP_Gun->SetupAttachment(RootComponent);

	FP_MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleLocation"));
	FP_MuzzleLocation->SetupAttachment(FP_Gun);
	FP_MuzzleLocation->SetRelativeLocation(FVector(0.2f, 48.4f, -10.6f));

	// Default offset from the character location for projectiles to spawn
	GunOffset = FVector(100.0f, 0.0f, 10.0f);

	// Note: The ProjectileClass and the skeletal mesh/anim blueprints for Mesh1P, FP_Gun, and VR_Gun 
	// are set in the derived blueprint asset named MyCharacter to avoid direct content references in C++.

	// Create VR Controllers.
	R_MotionController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("R_MotionController"));
	R_MotionController->MotionSource = FXRMotionControllerBase::RightHandSourceId;
	R_MotionController->SetupAttachment(RootComponent);
	L_MotionController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("L_MotionController"));
	L_MotionController->SetupAttachment(RootComponent);

	// Create a gun and attach it to the right-hand VR controller.
	// Create a gun mesh component
	VR_Gun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("VR_Gun"));
	VR_Gun->SetOnlyOwnerSee(true);			// only the owning player will see this mesh
	VR_Gun->bCastDynamicShadow = false;
	VR_Gun->CastShadow = false;
	VR_Gun->SetupAttachment(R_MotionController);
	VR_Gun->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));

	VR_MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("VR_MuzzleLocation"));
	VR_MuzzleLocation->SetupAttachment(VR_Gun);
	VR_MuzzleLocation->SetRelativeLocation(FVector(0.000004, 53.999992, 10.000000));
	VR_MuzzleLocation->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));		// Counteract the rotation of the VR gun model.

	// Uncomment the following line to turn motion controllers on by default:
	//bUsingMotionControllers = true;
	


}

void AA1Character::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
	
	

	GetWorldTimerManager().SetTimer(StartTimerHandle, this, &AA1Character::AdvanceTimer, 1.0f, true);

	//Attach gun mesh component to Skeleton, doing it here because the skeleton is not yet created in the constructor
	FP_Gun->AttachToComponent(Mesh1P, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));

	// Show or hide the two versions of the gun based on whether or not we're using motion controllers.
	if (bUsingMotionControllers)
	{
		VR_Gun->SetHiddenInGame(false, true);
		Mesh1P->SetHiddenInGame(true, true);
	}
	else
	{
		VR_Gun->SetHiddenInGame(true, true);
		Mesh1P->SetHiddenInGame(false, true);
	}
	


}

//////////////////////////////////////////////////////////////////////////
// Input

void AA1Character::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	check(PlayerInputComponent);
	
	// Bind jump events
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	// Bind fire event
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AA1Character::OnFire);

	PlayerInputComponent->BindAction("Action", IE_Pressed, this, &AA1Character::PickUp);

	// Enable touchscreen input
	EnableTouchscreenMovement(PlayerInputComponent);

	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &AA1Character::OnResetVR);

//Pause
	PlayerInputComponent->BindAction("Pause", IE_Pressed, this, &AA1Character::isPause);

	//UseGrenade
	PlayerInputComponent->BindAction("UseGrenade", IE_Pressed, this, &AA1Character::UseGrenade);

	PlayerInputComponent->BindAction("UseTimeBomb", IE_Pressed, this, &AA1Character::UseTimeBomb);


	// Bind movement events
	PlayerInputComponent->BindAxis("MoveForward", this, &AA1Character::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AA1Character::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AA1Character::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AA1Character::LookUpAtRate);
}

void AA1Character::PickUp()
{	
	//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, TEXT("Hello"));
	const FVector ForwardVector = FirstPersonCameraComponent->GetForwardVector();
	if (CanPickup) {
		
		TArray <AActor*> FoundActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMyKey::StaticClass(), FoundActors);
		currentItem = Cast<AMyKey>(FoundActors[0]);

		IInteractable::Execute_Interact(currentItem);
	}
}

void AA1Character::UseGrenade()
{	
	if (holdingGrenade==true && grenadeUsed == false) {
		grenadeUsed = true;
		holdingGrenade = false;
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("You used a grenade"));
	}
	if (holdingGrenade == true && grenadeUsed == true) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("You can't use two grenades at a time"));
	}
	if (holdingGrenade ==false) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("You don't have a grenade"));
	}
}

void AA1Character::UseTimeBomb()
{
	if (holdingBomb == true && bombUsed == false) {
		bombUsed = true;
		holdingBomb = false;
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("You used a Time Bomb"));
	}
	if (holdingBomb == true && bombUsed == true) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("You can't use two Time Bomb at a time"));
	}
	if (holdingBomb == false && bombUsed == false) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("You don't have a Time Bomb"));
	}

}

void AA1Character::OnFire()
{
	CallMyTrace();
	// try and fire a projectile
	/*
	if (ProjectileClass != NULL)
	{
		UWorld* const World = GetWorld();
		if (World != NULL)
		{
			if (bUsingMotionControllers)
			{
				const FRotator SpawnRotation = VR_MuzzleLocation->GetComponentRotation();
				const FVector SpawnLocation = VR_MuzzleLocation->GetComponentLocation();
				World->SpawnActor<AA1Projectile>(ProjectileClass, SpawnLocation, SpawnRotation);
			}
			else
			{
				const FRotator SpawnRotation = GetControlRotation();
				// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
				const FVector SpawnLocation = ((FP_MuzzleLocation != nullptr) ? FP_MuzzleLocation->GetComponentLocation() : GetActorLocation()) + SpawnRotation.RotateVector(GunOffset);

				//Set Spawn Collision Handling Override
				FActorSpawnParameters ActorSpawnParams;
				ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

				// spawn the projectile at the muzzle
				World->SpawnActor<AA1Projectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
			}
		}
	}

	// try and play the sound if specified
	if (FireSound != NULL)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
	}

	// try and play a firing animation if specified
	if (FireAnimation != NULL)
	{
		// Get the animation object for the arms mesh
		UAnimInstance* AnimInstance = Mesh1P->GetAnimInstance();
		if (AnimInstance != NULL)
		{
			AnimInstance->Montage_Play(FireAnimation, 1.f);
		}
	}*/
}

void AA1Character::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void AA1Character::BeginTouch(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	if (TouchItem.bIsPressed == true)
	{
		return;
	}
	if ((FingerIndex == TouchItem.FingerIndex) && (TouchItem.bMoved == false))
	{
		OnFire();
	}
	TouchItem.bIsPressed = true;
	TouchItem.FingerIndex = FingerIndex;
	TouchItem.Location = Location;
	TouchItem.bMoved = false;
}

void AA1Character::EndTouch(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	if (TouchItem.bIsPressed == false)
	{
		return;
	}
	TouchItem.bIsPressed = false;
}

//Commenting this section out to be consistent with FPS BP template.
//This allows the user to turn without using the right virtual joystick

//void AA1Character::TouchUpdate(const ETouchIndex::Type FingerIndex, const FVector Location)
//{
//	if ((TouchItem.bIsPressed == true) && (TouchItem.FingerIndex == FingerIndex))
//	{
//		if (TouchItem.bIsPressed)
//		{
//			if (GetWorld() != nullptr)
//			{
//				UGameViewportClient* ViewportClient = GetWorld()->GetGameViewport();
//				if (ViewportClient != nullptr)
//				{
//					FVector MoveDelta = Location - TouchItem.Location;
//					FVector2D ScreenSize;
//					ViewportClient->GetViewportSize(ScreenSize);
//					FVector2D ScaledDelta = FVector2D(MoveDelta.X, MoveDelta.Y) / ScreenSize;
//					if (FMath::Abs(ScaledDelta.X) >= 4.0 / ScreenSize.X)
//					{
//						TouchItem.bMoved = true;
//						float Value = ScaledDelta.X * BaseTurnRate;
//						AddControllerYawInput(Value);
//					}
//					if (FMath::Abs(ScaledDelta.Y) >= 4.0 / ScreenSize.Y)
//					{
//						TouchItem.bMoved = true;
//						float Value = ScaledDelta.Y * BaseTurnRate;
//						AddControllerPitchInput(Value);
//					}
//					TouchItem.Location = Location;
//				}
//				TouchItem.Location = Location;
//			}
//		}
//	}
//}

void AA1Character::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void AA1Character::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void AA1Character::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AA1Character::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

bool AA1Character::EnableTouchscreenMovement(class UInputComponent* PlayerInputComponent)
{
	if (FPlatformMisc::SupportsTouchInput() || GetDefault<UInputSettings>()->bUseMouseForTouch)
	{
		PlayerInputComponent->BindTouch(EInputEvent::IE_Pressed, this, &AA1Character::BeginTouch);
		PlayerInputComponent->BindTouch(EInputEvent::IE_Released, this, &AA1Character::EndTouch);

		return true;
	}
	
	return false;
}

void AA1Character::healthDec(float x)
{
	if (x >= health) {
		health = 0;
	}
	else {health -= x;}
	
	if (health <= 0) {
		health = 0;
	};
}

void AA1Character::healthInc(float x)
{
	
	health = health+x;
	
	if (health >= 100) {
		health = 100;
	};

}

void AA1Character::getHealth()
{
	health;
}

void AA1Character::waterDec(float x )
{	
	if (x >= water) {
		water = 0;
	}
	else {water -= x;}
	

}

void AA1Character::waterInc(float x)
{
	
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("water_character!"));
	water += x;

	if (water >= 100) {
		water = 100;
	};

}

void AA1Character::getWater()
{
	water;
}

void AA1Character::foodDec(float x)
{
	

	if (x>= food ) {
		food = 0;
	}
	else { food -= x; }
}

void AA1Character::foodInc(float x)
{
	food += x;
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("food _character!"));


	if (food >= 100) {
		food = 100;
	};
}

void AA1Character::getFood()
{
	food;
}

void AA1Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	if (ResetTimer && playing && !pause ) {
		//health, water and food decrease by 1 each second
		countDown -= DeltaTime;
		if (countDown <= 0) {
			if (invincibile == false){
			healthDec(1);
			waterDec(1);
			foodDec(1);
			}
			if (grenadeUsed) {
				if (GrenadeCountDown > 0) {
					GrenadeCountDown -= 1;
				}if (GrenadeCountDown <= 0) {
					grenadeUsed = false;
					GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Stun Time is Over, Enemy able to move again"));
					GrenadeCountDown = 6;
				}
			}
			if (invincibile) {
				if (invincibileCountDown > 0) {
					invincibileCountDown -= 1;
				
				}
				else { 
					invincibile = false;
					invincibileCountDown = 6;
					GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Beware! Invincible Time is Over! "));
				}
			}
			
			//extra function: decrease wlking speed and blur out vision of player when food/ water levels drop to certain amount 
			if (water >= 40 && food >= 40) {
				blurredVision = false; 
				GetCharacterMovement()->MaxWalkSpeed = MaxSpeed;
			}
			if (water <= 40 || food <= 40) {
				//decrease walking speed, make it the same as the enemies
				GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
				if (water <= 30|| food <= 30) {
					blurredVision = true;
				}
				else { blurredVision = false; }
			}

			

			countDown = SpaenInterval;
			getHealth();
			
		}
		
	}

	if (pause) {
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Yellow, "Pausing");
	}
	
	checkDead();

}

void AA1Character::AdvanceTimer()
{
	--StartTime;
	if (StartTime < 1) {
		ResetTimer = true;
	}
}

void AA1Character::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		

		if (OtherActor->GetClass()->ImplementsInterface(UInteractable::StaticClass())) {


			IInteractable::Execute_Interact(OtherActor);
			

			
		}

	}
}
void AA1Character::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{	

}

void AA1Character::startClicked()
{
	playing =true;
	
}

void AA1Character::isPause()
{
	
	 pause = true;

}

void AA1Character::checkDead()
{
	if (health <= 0 || water <= 0 || food <= 0) {
		dead = true;
	
	}
	
}

void AA1Character::checkWon()
{
	won = true;
	if (won) {
		UE_LOG(LogTemp, Warning, TEXT("You Win!!!"));
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, "You Win!!!");
	}
}

bool AA1Character::Trace(UWorld* World, TArray<AActor*>& ActorsToIgnore, const FVector& Start, const FVector& End, FHitResult& HitOut, ECollisionChannel CollisionChannel=ECC_Pawn, bool ReturnPhysMat=false)
{
	// The World parameter refers to our game world (map/level) 
	// If there is no World, abort
	if (!World)
	{
		return false;
	}

	// Set up our TraceParams object
	FCollisionQueryParams TraceParams(FName(TEXT("My Trace")), true, ActorsToIgnore[0]);

	// Should we simple or complex collision?
	TraceParams.bTraceComplex = true;

	// We don't need Physics materials 
	TraceParams.bReturnPhysicalMaterial = ReturnPhysMat;

	// Add our ActorsToIgnore
	TraceParams.AddIgnoredActors(ActorsToIgnore);

	// When we're debugging it is really useful to see where our trace is in the world
	// We can use World->DebugDrawTraceTag to tell Unreal to draw debug lines for our trace
	// (remove these lines to remove the debug - or better create a debug switch!)
	const FName TraceTag("MyTraceTag");
	World->DebugDrawTraceTag = TraceTag;
	TraceParams.TraceTag = TraceTag;


	// Force clear the HitData which contains our results
	HitOut = FHitResult(ForceInit);

	// Perform our trace
	World->LineTraceSingleByChannel
	(
		HitOut,		//result
		Start,	//start
		End, //end
		CollisionChannel, //collision channel
		TraceParams
	);

	// If we hit an actor, return true
	return (HitOut.GetActor() != NULL);
}

void AA1Character::CallMyTrace()
{
	// Get the location of the camera (where we are looking from) and the direction we are looking in
	const FVector Start = FirstPersonCameraComponent->GetComponentLocation();
	const FVector ForwardVector = FirstPersonCameraComponent->GetForwardVector();

	// How for in front of our character do we want our trace to extend?
	// ForwardVector is a unit vector, so we multiply by the desired distance
	const FVector End = Start + ForwardVector * 1256;

	// Force clear the HitData which contains our results
	FHitResult HitData(ForceInit);

	// What Actors do we want our trace to Ignore?
	TArray<AActor*> ActorsToIgnore;

	//Ignore the player character - so you don't hit yourself!
	ActorsToIgnore.Add(this);

	// Call our Trace() function with the paramaters we have set up
	// If it Hits anything
	if (Trace(GetWorld(), ActorsToIgnore, Start, End, HitData, ECC_Visibility, false))
	{
		// Process our HitData
		if (HitData.GetActor())
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, TEXT("Name: ")+ HitData.GetActor()->GetName());
			UE_LOG(LogClass, Warning, TEXT("This is"), *HitData.GetActor()->GetName());
			ProcessTraceHit(HitData);

		}
		else
		{
			// The trace did not return an Actor
			// An error has occurred
			// Record a message in the error log
		}
	}
	else
	{
		// We did not hit an Actor
		//ClearPickupInfo();

	}

}

void AA1Character::ProcessTraceHit(FHitResult& HitOut)
{	

	
	if (HitOut.GetActor()->GetClass()->ImplementsInterface(UInteractable::StaticClass()))
	{
		//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Orange, TEXT("Actor IS Interactable!"));

		if (HitOut.GetActor()->GetClass()->IsChildOf(AMyKey::StaticClass()) && !CanPickup) {
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, TEXT("Descirption: A golen key. Can be used to unlock a switch. "));
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, TEXT("Press 'E' to pick up"));
			CanPickup = true;
		}
		if (HitOut.GetActor()->GetClass()->IsChildOf(ASwitch::StaticClass()) && !CanPickup) {
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, TEXT("Descirption:A white switch."));
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, TEXT("Click again to interact"));
			CanPickup = true;
		}
		else {
			
			IInteractable::Execute_Interact(HitOut.GetActor());
			CanPickup = false;
		}
		
	}
	else
	{

		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Orange, TEXT("Actor is NOT Interactable!"));
		//UE_LOG(LogClass, Warning, TEXT("Actor is NOT Interactable!"));
		//ClearPickupInfo();
	}
}

void AA1Character::AddToInventory(AActor * actor)
{		
		
		
		_inventory.Add(actor);
		CanPickup = false;

		//UE_LOG(LogClass, Log, TEXT("This is %s"), *actor->GetName());
		//UE_LOG(LogClass, Log, TEXT("There are %s"), _inventory);
		//PrintInventory();
}

void AA1Character::RemoveFromInventory(AActor * actor)
{
	_inventory.Remove(actor);
	UE_LOG(LogClass, Log, TEXT("Remove"), *actor->GetName());
}

void AA1Character::PrintInventory()
{
	FString sInventory = "";
	for (AActor* actor : _inventory) {
		UE_LOG(LogClass, Log, TEXT("Inv: %s"), *actor->GetName());
	}
	


}
