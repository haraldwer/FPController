﻿#pragma once

#include "CoreMinimal.h"
#include "Project/Player/FPStateBase.h"
#include "Project/Player/Movement/FPMovementInputAction.h"
#include "FPMovementStateBase.generated.h"

class UFPAnimationStateBase;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECT_API UFPMovementStateBase : public UFPStateBase
{
	GENERATED_BODY()

public:
	virtual ~UFPMovementStateBase() override = default;

	// Override for custom behaviour
	virtual UClass* Input(EFPMovementInputAction anAction, float aValue);
	virtual UClass* OnLanded() { return nullptr; }
	virtual UClass* OnHit(const FHitResult& aHit) { return nullptr; }

	TSubclassOf<UFPAnimationStateBase> GetAnimation() const { return myAnimation; }

protected:

	// Helpers
	void Jump(FVector aDirection = FVector(0, 0, 1)) const;
	void MoveHorizontal(float aValue) const;
	void MoveVertical(float aValue) const;
	void LookHorizontal(float aValue) const;
	void LookVertical(float aValue) const;
	
	// Override for custom modification of input values
	virtual float GetSensitivity() const;

	UPROPERTY()
	TSubclassOf<UFPAnimationStateBase> myAnimation;
};