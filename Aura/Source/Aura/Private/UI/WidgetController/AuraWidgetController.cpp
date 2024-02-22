// Copyright Joel Herraiz.


#include "UI/WidgetController/AuraWidgetController.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/Data/AuraAbilityInfo.h"

void UAuraWidgetController::SetWidgetControllerParams(const FWidgetControllerParams& WCParams)
{
	PlayerController = WCParams.PlayerController;
	PlayerState = WCParams.PlayerState;
	AbilitySystemComponent = WCParams.AbilitySystemComponent;
	AttributeSet = WCParams.AttributeSet;
}

void UAuraWidgetController::BroadcastInitialValue()
{

}

void UAuraWidgetController::BindCallbacksToDependencies()
{

}

void UAuraWidgetController::BroadcastAbilityInfo()
{
	const auto AuraAsc = GetAbilitySystemComponent<UAuraAbilitySystemComponent>();
	if (!AuraAsc->bStartupAbilitiesGiven) return;

	FForEachAbility BroadcastDelegate;
	BroadcastDelegate.BindLambda([this, AuraAsc](const FGameplayAbilitySpec& AbilitySpec)
	{
		FAbilityInfo Info = AbilityInfo->FindAbilityInfoForTag(AuraAsc->GetAbilityTagFromSpec(AbilitySpec));
		Info.InputTag = AuraAsc->GetInputTagFromSpec(AbilitySpec);
		AbilityInfoDelegate.Broadcast(Info);
	});
	AuraAsc->ForEachAbility(BroadcastDelegate);
}
