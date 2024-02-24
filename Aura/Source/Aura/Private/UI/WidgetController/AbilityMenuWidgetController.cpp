// Copyright Joel Herraiz.


#include "UI/WidgetController/AbilityMenuWidgetController.h"

#include "NiagaraValidationRule.h"
#include "AbilitySystem/Data/AuraAbilityInfo.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"

void UAbilityMenuWidgetController::BroadcastInitialValue()
{
	BroadcastAbilityInfo();
}

void UAbilityMenuWidgetController::BindCallbacksToDependencies()
{
	GetAbilitySystemComponent<UAuraAbilitySystemComponent>()->AbilityStatusChanged.AddLambda([this](const FGameplayTag& AbilityTag, const FGameplayTag& StatusTag)
	{
		if (AbilityInfo)
		{
			FAbilityInfo Info = AbilityInfo->FindAbilityInfoForTag(AbilityTag);
			Info.StatusTag = StatusTag;
			AbilityInfoDelegate.Broadcast(Info);
		}
	});
}
