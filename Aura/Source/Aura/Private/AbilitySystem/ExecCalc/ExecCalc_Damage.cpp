// Copyright Joel Herraiz.

#include "AbilitySystem/ExecCalc/ExecCalc_Damage.h"

#include "AbilitySystemComponent.h"
#include "AuraAbilityTypes.h"
#include "AuraGameplayTags.h"
#include "AbilitySystem/AuraAbilitySystemLibrary.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/Data/CharacterClassInfo.h"
#include "Interaction/CombatInterface.h"

struct AuraDamageStatics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(Armor);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Evasion);
	DECLARE_ATTRIBUTE_CAPTUREDEF(ArmorPen);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CritChance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CritDamage);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CritRes);

	DECLARE_ATTRIBUTE_CAPTUREDEF(FireResistance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(LightningResistance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(ArcaneResistance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(PhysicalResistance);

	AuraDamageStatics()
	{
		/*
		 * Last parameter is a boolean to snapshot (capture) the Armor when the ability spec is created, instead of executed.
		 * See MMC_MaxHealth constructor for the "manual" version of this boilerplate code to capture an Attribute.
		 */
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, Armor, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, Evasion, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, ArmorPen, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, CritChance, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, CritDamage, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, CritRes, Target, false);

		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, FireResistance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, LightningResistance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, ArcaneResistance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, PhysicalResistance, Target, false);
	}
};

static const AuraDamageStatics& GetDamageStatics()
{
	static AuraDamageStatics DStatics;
	return DStatics;
}

UExecCalc_Damage::UExecCalc_Damage()
{
	RelevantAttributesToCapture.Add(GetDamageStatics().ArmorDef);
	RelevantAttributesToCapture.Add(GetDamageStatics().EvasionDef);
	RelevantAttributesToCapture.Add(GetDamageStatics().ArmorPenDef);
	RelevantAttributesToCapture.Add(GetDamageStatics().CritChanceDef);
	RelevantAttributesToCapture.Add(GetDamageStatics().CritDamageDef);
	RelevantAttributesToCapture.Add(GetDamageStatics().CritResDef);

	RelevantAttributesToCapture.Add(GetDamageStatics().FireResistanceDef);
	RelevantAttributesToCapture.Add(GetDamageStatics().LightningResistanceDef);
	RelevantAttributesToCapture.Add(GetDamageStatics().ArcaneResistanceDef);
	RelevantAttributesToCapture.Add(GetDamageStatics().PhysicalResistanceDef);
}

void UExecCalc_Damage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
                                              FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	TMap<FGameplayTag, FGameplayEffectAttributeCaptureDefinition> TagsToCaptureDefs;

	const FAuraGameplayTags& Tags = FAuraGameplayTags::Get();

	TagsToCaptureDefs.Add(Tags.Attributes_Secondary_Armor, GetDamageStatics().ArmorDef);
	TagsToCaptureDefs.Add(Tags.Attributes_Secondary_Evasion, GetDamageStatics().EvasionDef);
	TagsToCaptureDefs.Add(Tags.Attributes_Secondary_ArmorPenetration, GetDamageStatics().ArmorPenDef);
	TagsToCaptureDefs.Add(Tags.Attributes_Secondary_CriticalHitChance, GetDamageStatics().CritChanceDef);
	TagsToCaptureDefs.Add(Tags.Attributes_Secondary_CriticalHitResistance, GetDamageStatics().CritResDef);
	TagsToCaptureDefs.Add(Tags.Attributes_Secondary_CriticalDamage, GetDamageStatics().CritDamageDef);

	TagsToCaptureDefs.Add(Tags.Attributes_Resistance_Arcane, GetDamageStatics().ArcaneResistanceDef);
	TagsToCaptureDefs.Add(Tags.Attributes_Resistance_Fire, GetDamageStatics().FireResistanceDef);
	TagsToCaptureDefs.Add(Tags.Attributes_Resistance_Lightning, GetDamageStatics().LightningResistanceDef);
	TagsToCaptureDefs.Add(Tags.Attributes_Resistance_Physical, GetDamageStatics().PhysicalResistanceDef);

	TagsToCaptureDefs.Add(Tags.Attributes_Secondary_Armor, GetDamageStatics().ArmorDef);
	TagsToCaptureDefs.Add(Tags.Attributes_Secondary_Evasion, GetDamageStatics().EvasionDef);
	TagsToCaptureDefs.Add(Tags.Attributes_Secondary_ArmorPenetration, GetDamageStatics().ArmorPenDef);
	TagsToCaptureDefs.Add(Tags.Attributes_Secondary_CriticalHitChance, GetDamageStatics().CritChanceDef);
	TagsToCaptureDefs.Add(Tags.Attributes_Secondary_CriticalHitResistance, GetDamageStatics().CritResDef);
	TagsToCaptureDefs.Add(Tags.Attributes_Secondary_CriticalDamage, GetDamageStatics().CritDamageDef);

	TagsToCaptureDefs.Add(Tags.Attributes_Resistance_Arcane, GetDamageStatics().ArcaneResistanceDef);
	TagsToCaptureDefs.Add(Tags.Attributes_Resistance_Fire, GetDamageStatics().FireResistanceDef);
	TagsToCaptureDefs.Add(Tags.Attributes_Resistance_Lightning, GetDamageStatics().LightningResistanceDef);
	TagsToCaptureDefs.Add(Tags.Attributes_Resistance_Physical, GetDamageStatics().PhysicalResistanceDef);
	
	const UAbilitySystemComponent* SourceASC = ExecutionParams.GetSourceAbilitySystemComponent();
	const UAbilitySystemComponent* TargetASC = ExecutionParams.GetTargetAbilitySystemComponent();

	const AActor* SourceAvatar = SourceASC ? SourceASC->GetAvatarActor() : nullptr;
	const AActor* TargetAvatar = TargetASC ? TargetASC->GetAvatarActor() : nullptr;

	int32 SourcePlayerLevel = 1;
	int32 TargetPlayerLevel = 1;
	if (SourceAvatar->Implements<UCombatInterface>())
	{
		SourcePlayerLevel = ICombatInterface::Execute_GetPlayerLevel(SourceAvatar);
	}
	if (SourceAvatar->Implements<UCombatInterface>())
	{
		TargetPlayerLevel = ICombatInterface::Execute_GetPlayerLevel(TargetAvatar);
	}

	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();

	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();
	FAggregatorEvaluateParameters EvaluationParams;
	EvaluationParams.SourceTags = SourceTags;
	EvaluationParams.TargetTags = TargetTags;

	/*  Debuff */
	for (const auto& [DamageType, DebuffType] : Tags.DamageTypesToDebuffs)
	{
		const float TypeDamage = Spec.GetSetByCallerMagnitude(DamageType, false, -1.f);
		if (TypeDamage > 0.f)
		{
			const float SourceDebuffChance = Spec.GetSetByCallerMagnitude(Tags.Debuff_Chance, false, -1.f);
			float TargetDebuffResistance = 0.f;
			const FGameplayTag& ResistanceTag = Tags.DamageTypesToResistances[DamageType];
			ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(TagsToCaptureDefs[ResistanceTag], EvaluationParams, TargetDebuffResistance);
			TargetDebuffResistance = FMath::Max<float>(0.f, TargetDebuffResistance);

			const float EffectiveDebuffChance = SourceDebuffChance * (100.f - TargetDebuffResistance) / 100.f;
			const bool bApplyDebuff = FMath::RandRange(1, 100) < EffectiveDebuffChance;
			
			if (bApplyDebuff)
			{
				FGameplayEffectContextHandle ContextHandle = Spec.GetContext();

				UAuraAbilitySystemLibrary::SetHitAppliesDebuff(ContextHandle, true);
				UAuraAbilitySystemLibrary::SetDamageType(ContextHandle, DamageType);

				const float DebuffDamage = Spec.GetSetByCallerMagnitude(Tags.Debuff_Damage, false, -1.f);
				const float DebuffDuration = Spec.GetSetByCallerMagnitude(Tags.Debuff_Duration, false, -1.f);
				const float DebuffFrequency = Spec.GetSetByCallerMagnitude(Tags.Debuff_Frequency, false, -1.f);
				
				UAuraAbilitySystemLibrary::SetDebuffDamage(ContextHandle, DebuffDamage);
				UAuraAbilitySystemLibrary::SetDebuffDuration(ContextHandle, DebuffDuration);
				UAuraAbilitySystemLibrary::SetDebuffFrequency(ContextHandle, DebuffFrequency);
			}
		}
	}
	
	/* Get Damage Set by Caller Magnitude */
	float Damage = 0.f;
	for (const auto& Pair : FAuraGameplayTags::Get().DamageTypesToResistances)
	{
		const FGameplayTag DamageTypeTag = Pair.Key;
		const FGameplayTag ResistanceTag = Pair.Value;

		checkf(TagsToCaptureDefs.Contains(ResistanceTag), TEXT("TagsToCaptureDefs doesn't contain Tag: [%s] in ExecCalc_Damage"), *ResistanceTag.ToString());
		const FGameplayEffectAttributeCaptureDefinition CaptureDef = TagsToCaptureDefs[ResistanceTag];

		float DamageTypeValue = Spec.GetSetByCallerMagnitude(Pair.Key, false);

		float Resistance = 0.f;
		ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(CaptureDef, EvaluationParams, Resistance);
		constexpr float ResistanceCap = 50.f;
		Resistance = FMath::Clamp(Resistance, 0.f, ResistanceCap);

		DamageTypeValue *= ( 100.f - Resistance ) / 100.f;
		Damage += DamageTypeValue;
	}

	/* Evasion Chance Modifier */
	float TargetEvasionChance = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetDamageStatics().EvasionDef, EvaluationParams,
	                                                           TargetEvasionChance);
	TargetEvasionChance = FMath::Max<float>(0.f, TargetEvasionChance);

	FGameplayEffectContextHandle EffectContextHandle = Spec.GetContext();

	const bool bIsEvadedHit = FMath::RandRange(1, 100) < TargetEvasionChance;

	UAuraAbilitySystemLibrary::SetIsEvadedHit(EffectContextHandle, bIsEvadedHit);
	Damage = bIsEvadedHit ? Damage * 0.2f : Damage;
	
	/* Defense Penetration Modifier */
	float TargetArmor = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetDamageStatics().ArmorDef, EvaluationParams,
	                                                           TargetArmor);
	TargetEvasionChance = FMath::Max<float>(0.f, TargetArmor);

	float SourceArmorPen = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetDamageStatics().ArmorPenDef, EvaluationParams,
	                                                           SourceArmorPen);
	TargetEvasionChance = FMath::Max<float>(0.f, SourceArmorPen);

	const UCharacterClassInfo* CharacterClassInfo = UAuraAbilitySystemLibrary::GetCharacterClassInfo(SourceAvatar);
	const FRealCurve* ArmorPenCurve = CharacterClassInfo->DamageCalculationCoefficients->FindCurve(
		FName("ArmorPen"), FString());
	const float ArmorPenCoefficient = ArmorPenCurve->Eval(SourcePlayerLevel);

	const float EffectiveArmor = TargetArmor * FMath::Max<float>(0.f, 100 - SourceArmorPen * ArmorPenCoefficient) /
		100.f;

	const FRealCurve* EffectiveArmorCurve = CharacterClassInfo->DamageCalculationCoefficients->FindCurve(
		FName("EffectiveArmor"), FString());
	const float EffectiveArmorCoefficient = EffectiveArmorCurve->Eval(TargetPlayerLevel);

	Damage *= (100 - EffectiveArmor * EffectiveArmorCoefficient) / 100.f;

	/* Critical Hit Modifier */

	float SourceCritChance = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetDamageStatics().CritChanceDef, EvaluationParams,
	                                                           SourceCritChance);
	SourceCritChance = FMath::Max<float>(0.f, SourceCritChance);

	float TargetCritRes = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetDamageStatics().CritResDef, EvaluationParams,
	                                                           TargetCritRes);
	TargetCritRes = FMath::Max<float>(0.f, TargetCritRes);

	float SourceCritDamage = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetDamageStatics().CritDamageDef, EvaluationParams,
	                                                           SourceCritDamage);
	SourceCritDamage = FMath::Max<float>(0.f, SourceCritDamage);

	const FRealCurve* CritResCoefficientCurve = CharacterClassInfo->DamageCalculationCoefficients->FindCurve(
		FName("CritResCoefficient"), FString());
	const float CritResCoefficient = CritResCoefficientCurve->Eval(TargetPlayerLevel);

	const float EffectiveCritChance = SourceCritChance - TargetCritRes * CritResCoefficient;
	const bool bIsCriticalHit = FMath::RandRange(1, 100) < EffectiveCritChance;

	UAuraAbilitySystemLibrary::SetIsCriticalHit(EffectContextHandle, bIsCriticalHit);
	Damage = bIsCriticalHit ? 1.5f * SourceCritDamage * Damage : Damage;

	const FGameplayModifierEvaluatedData EvaluatedData(UAuraAttributeSet::GetIncomingDamageAttribute(),
	                                                   EGameplayModOp::Additive, Damage);
	OutExecutionOutput.AddOutputModifier(EvaluatedData);
}
