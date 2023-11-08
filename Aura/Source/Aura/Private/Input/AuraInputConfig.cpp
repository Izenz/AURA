// Copyright Joel Herraiz.


#include "Input/AuraInputConfig.h"

const UInputAction* UAuraInputConfig::FindAbilityInputActionForTag(const FGameplayTag& InputTag, bool bLogNotFound /*= false*/) const
{
	for (const FAuraInputAction& Action : AbilityInputActions)
	{
		if (Action.InputTag.MatchesTagExact(InputTag) && Action.InputAction != nullptr)
		{
			return Action.InputAction;
		}
	}

	if (bLogNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT("AbilityInputAction not found for tag: [%s], on InputConfig [%s]"),
			*InputTag.ToString(), *GetNameSafe(this));
	}

	return nullptr;
}
