﻿#include "FPMovementStateGrapple.h"

#include "FPMovementStateInAir.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Project/Gameplay/GrapplePoint.h"
#include "Project/Player/FPCharacter.h"
#include "Project/Player/Animation/FPAnimator.h"

UClass* UFPMovementStateGrapple::Update(float aDT)
{
	const auto timer = GetTime() - myTimeStamp;
	auto& movement = GetCharacterMovement();
	
	if (timer < myFreezeTime)
	{
		const float part = 1.0f - timer / myFreezeTime;
		movement.Velocity = myStartVelocity * part;
		return nullptr;
	}
	
	const auto diff = myTargetLocation - GetCharacter().GetActorLocation();
	movement.Velocity = diff.GetSafeNormal() * mySpeed * FVector(
		mySpeedMulHorizontal,
		mySpeedMulHorizontal,
		mySpeedMulVertical);

	if (timer > myFreezeTime + myReleaseTime)
		return UFPMovementStateInAir::StaticClass();
	
	if(diff.SizeSquared() < myReleaseDist * myReleaseDist)
		return UFPMovementStateInAir::StaticClass();
	
	return nullptr;
}

UClass* UFPMovementStateGrapple::Input(EFPMovementInputAction anAction, float aValue)
{
	Super::Input(anAction, aValue);

	CHECK_RETURN(anAction != EFPMovementInputAction::GRAPPLE, nullptr)

	const auto timer = GetTime() - myTimeStamp;
	CHECK_RETURN(timer < myCooldown, nullptr);
	
	TArray<AActor*> actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AGrapplePoint::StaticClass(), actors);

	const FVector forward = GetCamera().GetForwardVector();
	float dot = -1;
	AActor* ptr = nullptr;
	
	for(const auto& it : actors)
	{
		auto diff = (it->GetTransform().GetTranslation() - GetActorTransform().GetTranslation());
		if(diff.SizeSquared() < myDist * myDist)
		{
			diff.Normalize();
			const auto currDot = FVector::DotProduct(forward, diff);
			if(currDot > myDot && (!ptr || currDot > dot))
			{
				ptr = it; 
				dot = currDot;
			}
		}
	}

	CHECK_RETURN(!ptr, nullptr);
	myTargetLocation = ptr->GetTransform().GetTranslation();
	
	return StaticClass();
}

void UFPMovementStateGrapple::Enter()
{
	myTimeStamp = GetTime();
	
	const auto& movement = GetCharacterMovement();
	if (movement.IsWalking())
		Jump(FVector(0.0f, 0.0f, 1.0f));

	myStartVelocity = movement.GetLastUpdateVelocity();
	
	GetAnimator().StartGrapple();
		
	Super::Enter();
}

void UFPMovementStateGrapple::Exit()
{
	Super::Exit();
}
