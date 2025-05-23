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
	* Meta Attributes 
	*/

	Instance.Attributes_Meta_IncomingExp =
		UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Attributes.Meta.IncomingExp"),
			FString("Incoming Exp Meta Attribute."));
	
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
	Instance.Damage_Physical = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Damage.Physical"),
		FString("Physical Damage Type")
		);
	Instance.InputTag_Passive_1 =
		UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("InputTag.Passive.1"),
			FString("Input tag for Passive Skill 1."));
	Instance.InputTag_Passive_2 =
		UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("InputTag.Passive.2"),
			FString("Input tag for Passive Skill 2."));

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
	Instance.Attributes_Resistance_Physical = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Resistance.Physical"),
		FString("Resistance to Physical damage")
		);

	Instance.Debuff_Burn = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Debuff.Burn"),
		FString("Burn Debuff: Applies damage over time.")
		);
	Instance.Debuff_Stun = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Debuff.Stun"),
		FString("Stun Debuff: Immobilizes for a period of time.")
		);
	Instance.Debuff_Curse = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Debuff.Curse"),
		FString("Curse Debuff: Reduces movement and attack speed.")
		);
	Instance.Debuff_Bleed = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Debuff.Bleed"),
		FString("Bleed Debuff: Applies massive damage when stacked.")
		);

	Instance.Debuff_Chance = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Debuff.Chance"),
		FString("Debuff Chance.")
		);
	Instance.Debuff_Damage = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Debuff.Damage"),
		FString("Debuff value.")
		);
	Instance.Debuff_Frequency = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Debuff.Frequency"),
		FString("Debuff Tick Frequency.")
		);
	Instance.Debuff_Duration = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Debuff.Duration"),
		FString("debuff Duration in seconds.")
		);

	/* Map of Damage Types to Resistances */
	Instance.DamageTypesToResistances.Add(Instance.Damage_Fire, Instance.Attributes_Resistance_Fire);
	Instance.DamageTypesToResistances.Add(Instance.Damage_Lightning, Instance.Attributes_Resistance_Lightning);
	Instance.DamageTypesToResistances.Add(Instance.Damage_Arcane, Instance.Attributes_Resistance_Arcane);
	Instance.DamageTypesToResistances.Add(Instance.Damage_Physical, Instance.Attributes_Resistance_Physical);

	Instance.DamageTypesToDebuffs.Add(Instance.Damage_Fire, Instance.Debuff_Burn);
	Instance.DamageTypesToDebuffs.Add(Instance.Damage_Lightning, Instance.Debuff_Stun);
	Instance.DamageTypesToDebuffs.Add(Instance.Damage_Arcane, Instance.Debuff_Curse);
	Instance.DamageTypesToDebuffs.Add(Instance.Damage_Physical, Instance.Debuff_Bleed);

	/* Abilities */
	Instance.Abilities_Attack = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.Attack"),
		FString("Attack Ability Tag.")
		);
	Instance.Abilities_Summon = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.Summon"),
		FString("Summon Ability Tag.")
		);
	Instance.Abilities_Stagger = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.Stagger"),
		FString("Stagger Ability (Mechanic) Tag.")
		);

	Instance.Abilities_Status_Eligible = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.Status.Eligible"),
		FString("Ability Status Eligible Tag.")
		);
	Instance.Abilities_Status_Equipped = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.Status.Equipped"),
		FString("Ability Status Equipped Tag.")
		);
	Instance.Abilities_Status_Locked = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.Status.Locked"),
		FString("Ability Status Locked Tag.")
		);
	Instance.Abilities_Status_Unlocked = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.Status.Unlocked"),
		FString("Ability Status Unlocked Tag.")
		);
	
	Instance.Abilities_Fire_FireBolt = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.Fire.FireBolt"),
		FString("Fire Bolt Skill Ability Tag.")
		);

	Instance.Abilities_Lightning_Electrocute = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.Lightning.Electrocute"),
		FString("Electrocute Skill Ability Tag.")
		);

	Instance.Abilities_Type_Offensive = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.Type.Offensive"),
		FString("Tag for Offensive/Active Abilities.")
		);
	Instance.Abilities_Type_Passive = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.Type.Passive"),
		FString("Tag for Passive Abilities.")
		);
	Instance.Abilities_Type_Mechanic = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.Type.Mechanic"),
		FString("Tag for mechanics implemented by an Ability.")
		);

	Instance.Abilities_None = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.None"),
		FString("Tag for no ability. Like nullptr for AbilityTags.")
		);

	/* Cool-downs */
	Instance.Cooldown_Fire_FireBolt = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Cooldown.Fire.FireBolt"),
		FString("Fire Bolt Cooldown Tag.")
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
	Instance.Combat_Socket_Tail = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Combat.Socket.Tail"),
		FString("Attack using Tail.")
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

	/* Player Tags */

	Instance.Player_Block_Input_Pressed = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Player.Block.Input.Pressed"),
	FString("Blocks Input Pressed on player while carrying this tag.")
	);
	
	Instance.Player_Block_Input_Held = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Player.Block.Input.Held"),
	FString("Blocks Input Held on player while carrying this tag.")
	);
	
	Instance.Player_Block_Input_Released = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Player.Block.Input.Released"),
	FString("Blocks Input Released on player while carrying this tag.")
	);
	
	Instance.Player_Block_CursorTrace = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Player.Block.CursorTrace"),
	FString("Blocks Cursor Tracing while player owns this tag.")
	);
}

