#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "FPCharacter.generated.h"

UCLASS()
class PROJECT_API AFPCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	
	AFPCharacter();

protected:
	
	virtual void BeginPlay() override;
	virtual void BeginDestroy() override;

public:

	virtual void TickActor(float DeltaTime, ELevelTick TickType, FActorTickFunction& ThisTickFunction) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Input
	void MoveHorizontal(float aValue);
	void MoveVertical(float aValue);
	void LookHorizontal(float aValue);
	void LookVertical(float aValue);

	virtual void Landed(const FHitResult& aHit) override;

	void SetCheckpoint(AActor* aActor);
	
	class UCameraComponent* GetCamera() const;
	class UFPAnimator* GetAnimator() const;
	class UFPMovement* GetMovement() const;
	class UFPCombat* GetCombat() const;
	class UCapsuleComponent* GetWallDetection() const;

	class AHand* GetRightHand() const;
	class AHand* GetLeftHand() const;
	
	void SetHalfHeight();
	void SetFullHeight();

private:
	
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
	
	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	void Die(FString anObjectName);

protected:

	// Components
	UPROPERTY(Instanced, EditDefaultsOnly, Category="Components")
	UCameraComponent* myCamera;
	UPROPERTY(Instanced, EditDefaultsOnly, Category="Components")
	class UFPMovement* myFPMovement;
	UPROPERTY(Instanced, EditDefaultsOnly, Category="Components")
	class UFPAnimator* myFPAnimator;
	UPROPERTY(Instanced, EditDefaultsOnly, Category="Components")
	class UFPCombat* myFPCombat;

	UPROPERTY(Instanced, EditDefaultsOnly, Category="Components")
	UCapsuleComponent* myWallDetection;
	
	// Hands
	UPROPERTY(EditDefaultsOnly, Category = "Hands")
	TSubclassOf<AActor> myHandBP;
	UPROPERTY(Instanced)
	class AHand* myLeftHand;
	UPROPERTY(Instanced)
	class AHand* myRightHand;

	// Gameplay
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay")
	int myRespawns = 2;
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay")
	float mySensitivity = 0.5f;
	
private:
	float myFullHeight = 0.0f;
	FVector myCheckpointLocation;
	bool myHasCheckpoint = true;
	int myRespawnCount = 0;
	bool myDiedThisFrame = false;
};
