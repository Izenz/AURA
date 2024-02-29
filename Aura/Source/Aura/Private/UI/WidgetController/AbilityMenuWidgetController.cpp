// Copyright Joel Herraiz.


#include "UI/WidgetController/AbilityMenuWidgetController.h"

#include "AuraGameplayTags.h"
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
	GetAbilitySystemComponent<UAuraAbilitySystemComponent>()->AbilityStatusChanged.AddLambda([this](const FGameplayTag& AbilityTag, const FGameplayTag& StatusTag, int32 AbilityLevel)
	{
		if (SelectedAbility.Ability.MatchesTagExact(AbilityTag))
		{
			SelectedAbility.Status = StatusTag;
			
			bool EnableSpendButton = false;
			bool EnableEquipButton = false;
			ShouldEnableButtons(StatusTag, CurrentSpellPoints, EnableSpendButton, EnableEquipButton);
			FString Desc;
			FString NextLvDesc;
			GetAbilitySystemComponent<UAuraAbilitySystemComponent>()->GetDescriptionByAbilityTag(AbilityTag, Desc, NextLvDesc);
			SpellGlobeSelectedDelegate.Broadcast(EnableSpendButton, EnableEquipButton, Desc, NextLvDesc);
		}
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
		CurrentSpellPoints = NumOfAbilityPoints;
		
		bool EnableSpendButton = false;
		bool EnableEquipButton = false;
		ShouldEnableButtons(SelectedAbility.Status, CurrentSpellPoints, EnableSpendButton, EnableEquipButton);
		FString Desc;
		FString NextLvDesc;
		GetAbilitySystemComponent<UAuraAbilitySystemComponent>()->GetDescriptionByAbilityTag(SelectedAbility.Ability, Desc, NextLvDesc);
		SpellGlobeSelectedDelegate.Broadcast(EnableSpendButton, EnableEquipButton, Desc, NextLvDesc);
	});
}

void UAbilityMenuWidgetController::AbilityGlobeSelected(const FGameplayTag& AbilityTag)
{
	const FAuraGameplayTags GameplayTags = FAuraGameplayTags::Get();
	const int32 AbilityPoints = GetPlayerState<AAuraPlayerState>()->GetPlayerAbilityPoints();
	FGameplayTag AbilityStatus;
	
	const bool IsTagValid = AbilityTag.IsValid();
	const bool IsTagNone = AbilityTag.MatchesTag(GameplayTags.Abilities_None);
	const FGameplayAbilitySpec* AbilitySpec = GetAbilitySystemComponent<UAuraAbilitySystemComponent>()->GetSpecFromAbilityTag(AbilityTag);
	const bool IsSpecValid = AbilitySpec != nullptr;
	
	if (!IsTagValid || IsTagNone || !IsSpecValid)
	{
		AbilityStatus = GameplayTags.Abilities_Status_Locked;
	}
	else
	{
		AbilityStatus = GetAbilitySystemComponent<UAuraAbilitySystemComponent>()->GetAbilityStatusFromSpec(*AbilitySpec);
	}

	SelectedAbility.Ability = AbilityTag;
	SelectedAbility.Status = AbilityStatus;
	
	bool EnableSpendButton = false;
	bool EnableEquipButton = false;
	ShouldEnableButtons(AbilityStatus, AbilityPoints, EnableSpendButton, EnableEquipButton);
	FString Desc;
	FString NextLvDesc;
	GetAbilitySystemComponent<UAuraAbilitySystemComponent>()->GetDescriptionByAbilityTag(AbilityTag, Desc, NextLvDesc);
	SpellGlobeSelectedDelegate.Broadcast(EnableSpendButton, EnableEquipButton, Desc, NextLvDesc);
}

void UAbilityMenuWidgetController::OnSpendAbilityPointPressed()
{
	if (const auto AuraAsc = GetAbilitySystemComponent<UAuraAbilitySystemComponent>())
	{
		AuraAsc->ServerSpendAbilityPoint(SelectedAbility.Ability);
	}
	
}

void UAbilityMenuWidgetController::ShouldEnableButtons(const FGameplayTag& AbilityStatus, const int32 AbilityPoints,
                                                       bool& EnableSpendButton, bool& EnableEquipButton)
{
	const FAuraGameplayTags GameplayTags = FAuraGameplayTags::Get();
	EnableEquipButton = false;
	EnableSpendButton = false;

	if (AbilityStatus.MatchesTagExact(GameplayTags.Abilities_Status_Equipped) ||
		AbilityStatus.MatchesTagExact(GameplayTags.Abilities_Status_Unlocked))
	{
		EnableEquipButton = true;
		EnableSpendButton = AbilityPoints > 0;
	}
	else if (AbilityStatus.MatchesTagExact(GameplayTags.Abilities_Status_Eligible))
	{
		EnableSpendButton = AbilityPoints > 0;
	}
}
