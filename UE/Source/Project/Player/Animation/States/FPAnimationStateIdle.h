#pragma once

#include "CoreMinimal.h"
#include "FPAnimationStateBase.h"
#include "FPAnimationStateIdle.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECT_API UFPAnimationStateIdle : public UFPAnimationStateBase
{
	GENERATED_BODY()

public:
	
	virtual UClass* Update(float aDT) override;

protected:

	UPROPERTY(EditDefaultsOnly)
	float myHandWobbleStrength = 2.0f;
	
	UPROPERTY(EditDefaultsOnly)
	float myHandWobbleSpeed = 1.0f;
	
	UPROPERTY(EditDefaultsOnly)
	float myCameraBobStrength = 3.0f;
	
	UPROPERTY(EditDefaultsOnly)
	float myCameraBobSpeed = 4.0f;
};
