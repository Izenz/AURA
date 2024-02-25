// Copyright Joel Herraiz.


#include "UI/WidgetController/AbilityMenuWidgetController.h"

#include "AbilitySystem/Data/AuraAbilityInfo.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "Player/AuraPlayerState.h"

void UAbilityMenuWidgetController::BroadcastInitialValue()
{
	BroadcastAbilityInfo();
	AbilityPointsChanged.Broadcast(GetPlayerState<AAuraPlayerState>()->GetPlayerAbilityPoints());
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

	GetPlayerState<AAuraPlayerState>()->OnAbilityPointsChangedDelegate.AddLambda([this](const int32 NumOfAbilityPoints)
	{
		AbilityPointsChanged.Broadcast(NumOfAbilityPoints);
	});
}
