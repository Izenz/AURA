// Copyright Joel Herraiz.


#include "AbilitySystem/Data/AttributeInfo.h"
#include "Aura/AuraLogChannels.h"

FAuraAttributeInfo UAttributeInfo::FindAttributeInfoForTag(const FGameplayTag& AttributeTag, bool bLogNoutFound /*= false*/) const
{
	for (const FAuraAttributeInfo& Info : AttributeInformation)
	{
		if (Info.AttributeTag == AttributeTag)
		{
			return Info;
		}
	}

	if (bLogNoutFound)
	{
		UE_LOG(LogAura, Error, TEXT("Cant find Info for Attribute Tag [%s] on AttributeInfo [%s]"),
			*AttributeTag.ToString(), *GetNameSafe(this));
	}

	return FAuraAttributeInfo();
}
