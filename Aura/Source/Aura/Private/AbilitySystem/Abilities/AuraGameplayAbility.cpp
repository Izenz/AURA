// Copyright Joel Herraiz.


#include "AbilitySystem/Abilities/AuraGameplayAbility.h"

FString UAuraGameplayAbility::GetDescription(int32 Level)
{
	return FString::Printf(TEXT("<Level>%d. </><Default>%s.</>"), Level, L"Default Ability Name - Lorem Ipsum");
}

FString UAuraGameplayAbility::GetNextLevelDescription(int32 Level)
{
	return FString::Printf(TEXT("<Default>Next Level: </><Level>%d</> \n<Default>Causes much more damage. </>"), Level);
}

FString UAuraGameplayAbility::GetDescriptionForLocked(int32 Level)
{
	return FString::Printf(TEXT("<Default>This skills unlocks at level: </><Level>%d</>"), Level);
}
