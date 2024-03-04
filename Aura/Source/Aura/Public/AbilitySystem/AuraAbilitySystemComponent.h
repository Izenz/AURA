// Copyright Joel Herraiz.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AuraAbilitySystemComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FEffectAssetTags, const FGameplayTagContainer& /* AssetTags */);
DECLARE_MULTICAST_DELEGATE(FAbilitiesGiven);
DECLARE_DELEGATE_OneParam(FForEachAbility, const FGameplayAbilitySpec&);
DECLARE_MULTICAST_DELEGATE_ThreeParams(FAbilityStatusChanged, const FGameplayTag& /* AbilityTag */, const FGameplayTag& /* StatusTag */, int32 /* AbilityLevel */);
DECLARE_MULTICAST_DELEGATE_FourParams(FAbilityEquipped, const FGameplayTag& /* AbilityTag */,
                                      const FGameplayTag& /* Status */, const FGameplayTag& /* Slot */,
                                      const FGameplayTag& /* Previous Slot */)

/**
 * 
 */
UCLASS()
class AURA_API UAuraAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
	
public:
	void OnAbilityActorInfoSet();

	/* Delegates */
	FEffectAssetTags EffectAssetTags;
	FAbilitiesGiven AbilitiesGiven;
	FAbilityStatusChanged AbilityStatusChanged;
	FAbilityEquipped AbilityEquipped;

	void AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& StartupAbilities);
	void AddCharacterPassiveAbilities(const TArray<TSubclassOf<UGameplayAbility>>& StartupPassiveAbilities);
	bool bStartupAbilitiesGiven = false;

	void AbilityInputTagHeld(const FGameplayTag& InputTag);
	void AbilityInputTagReleased(const FGameplayTag& InputTag);
	void ForEachAbility(const FForEachAbility& Delegate);

	static FGameplayTag GetAbilityTagFromSpec(const FGameplayAbilitySpec AbilitySpec);
	static FGameplayTag GetInputTagFromSpec(const FGameplayAbilitySpec AbilitySpec);
	static FGameplayTag GetAbilityStatusFromSpec(const FGameplayAbilitySpec& AbilitySpec);
	FGameplayTag GetStatusFromAbilityTag(const FGameplayTag& Tag);
	FGameplayTag GetInputTagFromAbilityTag(const FGameplayTag& Tag);
	/**
	 * Returns the Spec of the Ability that corresponds to the input AbilityTag, if this AbilitySystemComponent owns an Ability with a matching tag. Otherwise it returns nullptr.
	 * @param AbilityTag Tag corresponding to the Ability.
	 * @return Spec for the Ability with a tag that matches AbilityTag.
	 */
	FGameplayAbilitySpec* GetSpecFromAbilityTag(const FGameplayTag& AbilityTag);

	void UpgradeAttribute(const FGameplayTag& AttributeTag);

	UFUNCTION(Server, Reliable)
	void ServerUpgradeAttribute(const FGameplayTag& AttributeTag);

	bool GetDescriptionByAbilityTag(const FGameplayTag& AbilityTag, FString& OutDescription, FString& OutNextLvDescription);

	void UpdateAbilityStatuses(int32 CurrentLevel);

	UFUNCTION(Server, Reliable)
	void ServerSpendAbilityPoint(const FGameplayTag& AbilityTag);

	UFUNCTION(Server, Reliable)
	void ServerEquipAbility(const FGameplayTag& AbilityTag, const FGameplayTag& Slot);

	void ClientEquipAbility(const FGameplayTag& AbilityTag, const FGameplayTag& Status, const FGameplayTag& Slot,
	                        const FGameplayTag& PrevSlot) const;

	void ClearSlot(FGameplayAbilitySpec* Spec);
	void ClearAssignedSlotFromAbilities(const FGameplayTag& Slot);
	static bool IsAbilityAssignedTo(FGameplayAbilitySpec* Spec, const FGameplayTag& Slot);

protected:

	virtual void OnRep_ActivateAbilities() override;
	
	UFUNCTION(Client, Reliable)
	void ClientOnEffectApplied(UAbilitySystemComponent* AbilitySystemComponent,
		const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle);

	UFUNCTION(Client, Reliable)
	void ClientUpdateAbilityStatus(const FGameplayTag& AbilityTag, const FGameplayTag& StatusTag, int32 AbilityLevel);
};
