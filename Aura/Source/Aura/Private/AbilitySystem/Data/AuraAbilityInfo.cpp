// Copyright Joel Herraiz.


#include "AbilitySystem/Data/AuraAbilityInfo.h"

#include "Aura/AuraLogChannels.h"

FAbilityInfo UAuraAbilityInfo::FindAbilityInfoForTag(const FGameplayTag& GameplayTag, bool bLogIfNotFound) const
{
	for (const FAbilityInfo& Info : AbilitiesInformation)
	{
		if (Info.AbilityTag == GameplayTag)
		{
			return Info;
		}
	}

	if (bLogIfNotFound)
	{
		UE_LOG(LogAura, Error, TEXT("Can not find info for AbilityTag: [%s] on AbilityInfo: [%s]"), *GameplayTag.ToString(), *GetNameSafe(this));
	}

	return FAbilityInfo();
}
