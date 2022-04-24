﻿#pragma once

#include "CoreMinimal.h"
#include "FPAnimationStateBase.h"
#include "FPAnimationStateStrike.generated.h"

USTRUCT(BlueprintType)
struct FFPStrikeAnimEntry
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	FTransform myStart;
	
	UPROPERTY(EditDefaultsOnly)
	FTransform myEnd;
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECT_API UFPAnimationStateStrike : public UFPAnimationStateBase
{
	GENERATED_BODY()

public:
	
	virtual UClass* Update(float aDT) override;
	virtual void Enter() override;
	virtual int32 Priority() const override { return 2; }

protected:

	UPROPERTY(EditDefaultsOnly)
	TArray<FFPStrikeAnimEntry> myEntries;

	UPROPERTY(EditDefaultsOnly)
	class UCurveFloat* myCurve;
	
	UPROPERTY(EditDefaultsOnly)
	float myStrikeDuration = 0.3f; 
	
private:

	int32 myAnimIndex = 0;
	float myStrikeTimestamp = 0.0f; 

};
