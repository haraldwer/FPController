#include "FPCombatStateIdle.h"

#include "FPCombatStateNoSword.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Project/Player/Combat/FPCombat.h"

UClass* UFPCombatStateIdle::Update(float aDT)
{
	if (!GetCombat().GetSword())
		return UFPCombatStateNoSword::StaticClass();
	return nullptr;
}
