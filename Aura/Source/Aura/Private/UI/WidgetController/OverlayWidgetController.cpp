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
		.AddLambda(
			[this](const FOnAttributeChangeData& Data)
			{
				OnHealthChanged.Broadcast(Data.NewValue);
			}
	);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAS->GetMaxHealthAttribute())
		.AddLambda(
			[this](const FOnAttributeChangeData& Data)
			{
				OnMaxHealthChanged.Broadcast(Data.NewValue);
			}
	);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAS->GetManaAttribute())
		.AddLambda(
			[this](const FOnAttributeChangeData& Data)
			{
				OnManaChanged.Broadcast(Data.NewValue);
			}
	);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAS->GetMaxManaAttribute())
		.AddLambda(
			[this](const FOnAttributeChangeData& Data)
			{
				OnMaxManaChanged.Broadcast(Data.NewValue);
			}
	);

	Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent)->EffectAssetTags
		.AddLambda(
			[this](const FGameplayTagContainer& AssetTags)
			{
				for (const FGameplayTag& Tag : AssetTags)
				{
					// "A.1".MatchesTag("A") will return True, "A".MatchesTag("A.1") will return False
					FGameplayTag MessageTag = FGameplayTag::RequestGameplayTag(FName("Message"));
					if (!Tag.MatchesTag(MessageTag))	continue;

					const FString Msg = FString::Printf(TEXT("GE Tag: %s"), *Tag.ToString());
					GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, Msg);

					const FUIWidgetRow* Row = 
						GetDataTableRowByTag<FUIWidgetRow>(MessageWidgetDataTable, Tag);

					MessageWidgetRowDelegate.Broadcast(*Row);
				}

			}
	);

}