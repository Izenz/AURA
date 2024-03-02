// Copyright Joel Herraiz.

#include "AbilitySystem/Abilities/AuraFireBolt.h"
#include "AuraGameplayTags.h"

FString UAuraFireBolt::GetDescription(int32 Level)
{
	const int Damage = GetDamageByDamageType(Level, FAuraGameplayTags::Get().Damage_Fire);
	const float ManaCost = FMath::Abs(GetManaCost(Level));
	const float Cooldown = GetCooldown(Level);
	
	return FString::Printf(TEXT("<Title>FIRE BOLT Lv %d</>\n\n"
			"<Default>Mana Cost: </><ManaCost>%.2f</>\n"
			"<Default>Cooldown: </><Cooldown>%.2f</><Default> seconds.</>\n\n"
			"<Default>Launches </><Enhancement>%d</><Default> bolts of fire, exploding on impact and dealing </><Damage>%d</>"
			"<Default> fire damage with a chance to burn.</>"), Level, ManaCost, Cooldown, FMath::Min(Level, NumOfProjectiles), Damage);
}

FString UAuraFireBolt::GetNextLevelDescription(int32 Level)
{
	return GetDescription(Level);
}