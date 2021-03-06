
#include "Projectile.h"

#include "GameFramework/DamageType.h"
#include "Kismet/GameplayStatics.h"
#include "Project/Player/FPCharacter.h"
#include "Project/Player/Actors/Hand.h"
#include "Project/Player/Actors/Sword.h"

AProjectile::AProjectile()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	myStartTime = GetWorld()->GetTimeSeconds();
	myPreviousLocation = GetActorLocation();
}

void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Lifetime
	const float currentTime = GetWorld()->GetTimeSeconds();
	if (currentTime < myStartTime + myInitialDelay)
		return;
	
	if (currentTime > myStartTime + myLifetime + myInitialDelay)
	{
		myOutOfRange = true;
		Destroy();
		return;
	}

	const auto trans = GetTransform();
	
	// Move
	SetActorLocation(trans.GetLocation() + trans.TransformVector(myVelocity) * DeltaTime);
	
	// Trace between current and previous location
	TArray<FHitResult> hits;
	FCollisionQueryParams params;
	params.AddIgnoredActor(this);
	params.AddIgnoredActor(myInstigator.Get());
	if (GetWorld()->LineTraceMultiByChannel(hits, trans.GetLocation(), myPreviousLocation, ECC_Pawn, params))
	{
		for (auto& hit : hits)
		{
			if (!hit.bBlockingHit)
				continue;
			if (Cast<ASword>(hit.GetActor()))
				continue;
			if (Cast<AHand>(hit.GetActor()))
				continue;
			
			if (const auto character = Cast<AFPCharacter>(hit.GetActor()))
			{
				UGameplayStatics::ApplyDamage(character, 1.0f, nullptr, GetOwner(), UDamageType::StaticClass());
				Destroy();
			}
		}
	}

	if (GetWorld()->LineTraceMultiByChannel(hits, trans.GetLocation(), myPreviousLocation, ECC_WorldStatic, params))
	{
		for (const auto& hit : hits)
			if (hit.bBlockingHit)
				Destroy();
	}

	myPreviousLocation = trans.GetLocation();
}

void AProjectile::Destroyed()
{
	if (!myOutOfRange)
		CreateHitEffects();
	Super::Destroyed();
}

