// Copyright Joel Herraiz.


#include "UI/WidgetController/OverlayWidgetController.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"

void UOverlayWidgetController::BroadcastInitialValue()
{
	const UAuraAttributeSet* AuraAS = Cast<UAuraAttributeSet>(AttributeSet);

	OnHealthChanged.Broadcast(AuraAS->GetHealth());
	OnMaxHealthChanged.Broadcast(AuraAS->GetMaxHealth());
	OnManaChanged.Broadcast(AuraAS->GetMana());
	OnMaxManaChanged.Broadcast(AuraAS->GetMaxMana());

}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	const UAuraAttributeSet* AuraAS = Cast<UAuraAttributeSet>(AttributeSet);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAS->GetHealthAttribute())
		.AddUObject(this, &UOverlayWidgetController::HealthChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAS->GetMaxHealthAttribute())
		.AddUObject(this, &UOverlayWidgetController::MaxHealthChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAS->GetManaAttribute())
		.AddUObject(this, &UOverlayWidgetController::ManaChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAS->GetMaxManaAttribute())
		.AddUObject(this, &UOverlayWidgetController::MaxManaChanged);

	Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent)->EffectAssetTags.AddLambda(
		[this](const FGameplayTagContainer& AssetTags) 
		{
			for (const FGameplayTag& Tag : AssetTags)
			{
				// "A.1".MatchesTag("A") will return True, "A".MatchesTag("A.1") will return False
				FGameplayTag MessageTag = FGameplayTag::RequestGameplayTag(FName("Message"));
				if (!Tag.MatchesTag(MessageTag))	continue;

				const FString Msg = FString::Printf(TEXT("GE Tag: %s"), *Tag.ToString());
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, Msg);

				const FUIWidgetRow* Row = GetDataTableRowByTag<FUIWidgetRow>(MessageWidgetDataTable, Tag);
				MessageWidgetRowDelegate.Broadcast(*Row);
			}

		}
	);

}

void UOverlayWidgetController::HealthChanged(const FOnAttributeChangeData& Data) const
{
	OnHealthChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaxHealthChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxHealthChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::ManaChanged(const FOnAttributeChangeData& Data) const
{
	OnManaChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaxManaChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxManaChanged.Broadcast(Data.NewValue);
}
