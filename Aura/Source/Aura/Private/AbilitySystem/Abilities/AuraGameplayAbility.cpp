// Copyright Joel Herraiz.


#include "AbilitySystem/Abilities/AuraGameplayAbility.h"
#include "AbilitySystem/AuraAttributeSet.h"

FString UAuraGameplayAbility::GetDescription(int32 Level)
{
	return FString::Printf(TEXT("<Level>%d. </><Default>%s.</>"), Level, L"ERROR: This Ability should override GetDescription method!");
}

FString UAuraGameplayAbility::GetNextLevelDescription(int32 Level)
{
	return GetDescription(Level);
}

FString UAuraGameplayAbility::GetDescriptionForLocked(int32 Level)
{
	return FString::Printf(TEXT("<Default>This skills unlocks at level: </><Level>%d</>"), Level);
}

float UAuraGameplayAbility::GetManaCost(float InLevel) const
{
	float ManaCost = 0.f;
	if (const UGameplayEffect* EffectCost = GetCostGameplayEffect())
	{
		for (FGameplayModifierInfo Modifier : GetCostGameplayEffect()->Modifiers)
		{
			if (Modifier.Attribute == UAuraAttributeSet::GetManaAttribute())
			{
				Modifier.ModifierMagnitude.GetStaticMagnitudeIfPossible(InLevel, ManaCost);
				break;
			}
		}
	}

	return ManaCost;
}

float UAuraGameplayAbility::GetCooldown(float InLevel) const
{
	float Cooldown = 0.f;
	if (const UGameplayEffect* CooldownEffect = GetCooldownGameplayEffect())
	{
		CooldownEffect->DurationMagnitude.GetStaticMagnitudeIfPossible(InLevel, Cooldown);
	}

	return Cooldown;
}
