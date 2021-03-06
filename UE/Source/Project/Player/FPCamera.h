#pragma once

#include "CoreMinimal.h"
#include "FPComponentBase.h"
#include "FPCamera.generated.h"

UCLASS(ClassGroup=(Custom))
class PROJECT_API UFPCamera : public UFPActorComponentBase
{
	GENERATED_BODY()

public:
	UFPCamera();
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void BeginTick(float aDT);
	
	void SetHeight(float aHeight) { myHeight = aHeight; }
	void SetTargetHeight(float aHeight) { myTargetHeight = aHeight; }
	
	void AddAdditiveFov(float aFov) { myAdditiveFov += aFov; }
	void SetOffset(const FTransform& anOffset) { myOffset = anOffset; }
	void SetStepUpOffset(float anOffset) { myStepUpOffset = anOffset; }
	
protected:
	
	UPROPERTY(EditDefaultsOnly)
	float myCameraHeightSmoothing = 15.0f;
	
private:
	FTransform myOffset;
	float myStepUpOffset = 0.0f; 
	float myAdditiveFov = 0.0f;
	float myHeight = 1.0f;
	float myTargetHeight = 1.0f;
	float myOriginalHeight = 0.0f;
};
