// Copyright Joel Herraiz.


#include "AuraGameplayTags.h"
#include "GameplayTagsManager.h"

FAuraGameplayTags FAuraGameplayTags::Instance;

void FAuraGameplayTags::InitNativeGameplayTags()
{
	/*
	* Primary Attributes
	*/

	Instance.Attributes_Primary_Lethality =
		UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Attributes.Primary.Lethality"),
			FString("Increases combat prowess and stats such as critical damage, armor penetration and critical hit resistance."));
	Instance.Attributes_Primary_Intelligence =
		UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Attributes.Primary.Intelligence"),
			FString("Increases magical prowess and stats such as critical hit chance, mana regeneration and max mana."));
	Instance.Attributes_Primary_Agility =
		UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Attributes.Primary.Agility"),
			FString("Increases survivability and stats such as evasion, casting and movement speed."));
	Instance.Attributes_Primary_Vigor =
		UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Attributes.Primary.Vigor"),
			FString("Increases resilience and stats such as armor, max health and health regeneration"));


	/*
	* Secondary Attributes
	*/

	Instance.Attributes_Secondary_Armor =
		UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Attributes.Secondary.Armor"),
			FString("Reduces damage taken."));
	Instance.Attributes_Secondary_ArmorPenetration =
		UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Attributes.Secondary.ArmorPenetration"),
			FString("Increases the percentage of enemy armor ignored when attacking."));
	Instance.Attributes_Secondary_Evasion =
		UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Attributes.Secondary.Evasion"),
			FString("Increases chance to ignore incoming damage."));
	Instance.Attributes_Secondary_CriticalHitChance =
		UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Attributes.Secondary.CriticalHitChance"),
			FString("Increases chance to deal a critical hit when attacking."));
	Instance.Attributes_Secondary_CriticalDamage =
		UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Attributes.Secondary.CriticalDamage"),
			FString("Increases damage multiplier when critical hits are dealt."));
	Instance.Attributes_Secondary_CriticalHitResistance =
		UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Attributes.Secondary.CriticalHitResistance"),
			FString("Reduces chances of receiving a critical hit when being attacked."));
	Instance.Attributes_Secondary_HealthRegeneration =
		UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Attributes.Secondary.HealthRegeneration"),
			FString("Amount of health recovered per second."));
	Instance.Attributes_Secondary_ManaRegeneration =
		UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Attributes.Secondary.ManaRegeneration"),
			FString("Amount of mana recovered per second."));
	Instance.Attributes_Secondary_MaxHealth =
		UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Attributes.Secondary.MaxHealth"),
			FString("Maximum value for Health Points."));
	Instance.Attributes_Secondary_MaxMana =
		UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Attributes.Secondary.MaxMana"),
			FString("Maximum value for Mana Points."));

	/*
	* Input Tags 
	*/
	Instance.InputTag_LMB =
		UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("InputTag.LMB"),
			FString("Input tag for Left Mouse Button."));
	Instance.InputTag_RMB =
		UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("InputTag.RMB"),
			FString("Input tag for Right Mouse Button."));
	Instance.InputTag_1 =
		UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("InputTag.1"),
			FString("Input tag for the number 1 key."));
	Instance.InputTag_2 =
		UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("InputTag.2"),
			FString("Input tag for the number 2 key."));
	Instance.InputTag_3 =
		UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("InputTag.3"),
			FString("Input tag for the number 3 key."));
	Instance.InputTag_4 =
		UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("InputTag.4"),
			FString("Input tag for the number 4 key."));
	Instance.Damage =
		UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Damage"),
			FString("Damage."));
	Instance.Damage_Fire = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Damage.Fire"),
		FString("Fire Damage Type")
		);
	Instance.Damage_Lightning = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Damage.Lightning"),
		FString("Lightning Damage Type")
		);
	Instance.Damage_Arcane = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Damage.Arcane"),
		FString("Arcane Damage Type")
		);

	/* Resistances */
	
	Instance.Attributes_Resistance_Fire = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Resistance.Fire"),
		FString("Resistance to Fire damage")
		);
	Instance.Attributes_Resistance_Lightning = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Resistance.Lightning"),
		FString("Resistance to Lightning damage")
		);
	Instance.Attributes_Resistance_Arcane = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Resistance.Arcane"),
		FString("Resistance to Arcane damage")
		);

	/* Map of Damage Types to Resistances */
	Instance.DamageTypesToResistances.Add(Instance.Damage_Fire, Instance.Attributes_Resistance_Fire);
	Instance.DamageTypesToResistances.Add(Instance.Damage_Lightning, Instance.Attributes_Resistance_Lightning);
	Instance.DamageTypesToResistances.Add(Instance.Damage_Arcane, Instance.Attributes_Resistance_Arcane);
	
	/* Effects */
	Instance.Effects_Stagger =
		UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Effects.Stagger"),
			FString("Tag granted when hit reacting."));

	/* Abilities */
	Instance.Abilities_Attack = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.Attack"),
		FString("Attack Ability Tag.")
		);

	/* Combat Sockets */
	Instance.Combat_Socket_Weapon = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Combat.Socket.Weapon"),
		FString("Attack using Weapon.")
		);
	Instance.Combat_Socket_RightHand = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Combat.Socket.RightHand"),
		FString("Attack using Right Hand.")
		);
	Instance.Combat_Socket_LeftHand = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Combat.Socket.LeftHand"),
		FString("Attack using Left Hand.")
		);
	Instance.Montage_Attack_1 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Montage.Attack.1"),
		FString("Attack 1")
		);
	Instance.Montage_Attack_2 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Montage.Attack.2"),
		FString("Attack 2")
		);
	Instance.Montage_Attack_3 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Montage.Attack.3"),
		FString("Attack 3")
		);
	Instance.Montage_Attack_4 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Montage.Attack.4"),
		FString("Attack 4")
		);
}

