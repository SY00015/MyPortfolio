// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once
#include "Components/CapsuleComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyCharacter.h"
#include "EnemyAIController.h"
#include "A1Character.generated.h"

class UInputComponent;


UCLASS(config=Game)
class AA1Character : public ACharacter
{
	GENERATED_BODY()
	UPROPERTY(VisibleAnywhere, Category = "Trigger Capsule")
	class UCapsuleComponent* TriggerCapsule;

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	class USkeletalMeshComponent* Mesh1P;

	/** Gun mesh: 1st person view (seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USkeletalMeshComponent* FP_Gun;

	/** Location on gun mesh where projectiles should spawn. */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USceneComponent* FP_MuzzleLocation;

	/** Gun mesh: VR view (attached to the VR controller directly, no arm, just the actual gun) */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USkeletalMeshComponent* VR_Gun;

	/** Location on VR gun mesh where projectiles should spawn. */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USceneComponent* VR_MuzzleLocation;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FirstPersonCameraComponent;

	/** Motion controller (right hand) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UMotionControllerComponent* R_MotionController;

	/** Motion controller (left hand) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UMotionControllerComponent* L_MotionController;

public:
	AA1Character();

protected:
	virtual void BeginPlay();

public:
	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	/** Gun muzzle's offset from the characters location */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	FVector GunOffset;

	/** Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, Category=Projectile)
	TSubclassOf<class AA1Projectile> ProjectileClass;

	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	class USoundBase* FireSound;

	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class UAnimMontage* FireAnimation;

	/** Whether to use motion controller location for aiming. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	uint32 bUsingMotionControllers : 1;

protected:
	
	void PickUp();

	void Pause();

	void UseGrenade();

	void UseTimeBomb();

	/** Fires a projectile. */
	void OnFire();

	/** Resets HMD orientation and position in VR. */
	void OnResetVR();

	/** Handles moving forward/backward */
	void MoveForward(float Val);

	/** Handles stafing movement, left and right */
	void MoveRight(float Val);

	/**
	 * Called via input to turn at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	struct TouchData
	{
		TouchData() { bIsPressed = false;Location=FVector::ZeroVector;}
		bool bIsPressed;
		ETouchIndex::Type FingerIndex;
		FVector Location;
		bool bMoved;
	};
	void BeginTouch(const ETouchIndex::Type FingerIndex, const FVector Location);
	void EndTouch(const ETouchIndex::Type FingerIndex, const FVector Location);
	void TouchUpdate(const ETouchIndex::Type FingerIndex, const FVector Location);
	TouchData	TouchItem;
	
protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface

	/* 
	 * Configures input for touchscreen devices if there is a valid touch interface for doing so 
	 *
	 * @param	InputComponent	The input component pointer to bind controls to
	 * @returns true if touch controls were enabled.
	 */
	bool EnableTouchscreenMovement(UInputComponent* InputComponent);

public:
	/** Returns Mesh1P subobject **/
	FORCEINLINE class USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	/** Returns FirstPersonCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

	//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//health
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float health;

		void healthDec(float x);
		void healthInc(float x);
		void getHealth();

	//water
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float water;
		void waterDec(float x);
		void waterInc(float x);
		void getWater();

	//food 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float food;
		void foodDec(float x);
		void foodInc(float x);
		void getFood();

		virtual void Tick(float DeltaTime) override;

		//countdown functions 
		void AdvanceTimer();
	UPROPERTY(EditAnywhere)
		int32 StartTime;

		float countDown;

		float GrenadeCountDown;

		float invincibileCountDown;


		//TimerHandle 
		FTimerHandle StartTimerHandle;

	UPROPERTY(EditAnywhere)
		float SpaenInterval;
		bool ResetTimer = false;

		//Overlap 
	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


	UFUNCTION()
		void startClicked();

	
	//pause screen 
	void isPause();

	//player state
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool playing;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool pause;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool dead;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool won;


	//void checkWin();

	void checkDead();
	void checkWon();


	bool Trace(
		UWorld* World,
		TArray<AActor*>& ActorsToIgnore,
		const FVector& Start,
		const FVector& End,
		FHitResult& HitOut,
		ECollisionChannel CollisionChannel,
		bool ReturnPhysMat
	);

	void CallMyTrace();
	void ProcessTraceHit(FHitResult& HitOut);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class AMyKey* currentItem;
	
	FVector holdingComp;
	//FVector ForwardVector;
//	FHitResult Hit;
	bool CanPickup;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool holdingKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool holdingFuse;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool holdingGrenade;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool grenadeUsed;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool invincibile;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool holdingBomb;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bombUsed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool blurredVision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool EnemyAttack;


	float WalkSpeed;

	float MaxSpeed;

	TArray<AActor*>_inventory;

	void AddToInventory(AActor* actor);

	void RemoveFromInventory(AActor* actor);

	UFUNCTION (BlueprintCallable)
	void PrintInventory();
	void PickUpItem();

	class AEnemyCharacter* enemy;


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		bool spawnExplode;
};

