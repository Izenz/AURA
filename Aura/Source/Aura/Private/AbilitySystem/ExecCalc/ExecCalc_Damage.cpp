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
}

void UExecCalc_Damage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
                                              FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	const UAbilitySystemComponent* SourceASC = ExecutionParams.GetSourceAbilitySystemComponent();
	const UAbilitySystemComponent* TargetASC = ExecutionParams.GetTargetAbilitySystemComponent();

	const AActor* SourceAvatar = SourceASC ? SourceASC->GetAvatarActor() : nullptr;
	const AActor* TargetAvatar = TargetASC ? TargetASC->GetAvatarActor() : nullptr;

	const ICombatInterface* SourceCombatInterface = Cast<ICombatInterface>(SourceAvatar);
	const ICombatInterface* TargetCombatInterface = Cast<ICombatInterface>(TargetAvatar);

	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();

	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();
	FAggregatorEvaluateParameters EvaluationParams;
	EvaluationParams.SourceTags = SourceTags;
	EvaluationParams.TargetTags = TargetTags;

	/* Get Damage Set by Caller Magnitude */
	float Damage = Spec.GetSetByCallerMagnitude(FAuraGameplayTags::Get().Damage);

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
	const float ArmorPenCoefficient = ArmorPenCurve->Eval(SourceCombatInterface->GetPlayerLevel());

	const float EffectiveArmor = TargetArmor * FMath::Max<float>(0.f, 100 - SourceArmorPen * ArmorPenCoefficient) /
		100.f;

	const FRealCurve* EffectiveArmorCurve = CharacterClassInfo->DamageCalculationCoefficients->FindCurve(
		FName("EffectiveArmor"), FString());
	const float EffectiveArmorCoefficient = EffectiveArmorCurve->Eval(TargetCombatInterface->GetPlayerLevel());

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
	const float CritResCoefficient = CritResCoefficientCurve->Eval(TargetCombatInterface->GetPlayerLevel());

	const float EffectiveCritChance = SourceCritChance - TargetCritRes * CritResCoefficient;
	const bool bIsCriticalHit = FMath::RandRange(1, 100) < EffectiveCritChance;

	UAuraAbilitySystemLibrary::SetIsCriticalHit(EffectContextHandle, bIsCriticalHit);
	Damage = bIsCriticalHit ? 1.5f * SourceCritDamage * Damage : Damage;

	const FGameplayModifierEvaluatedData EvaluatedData(UAuraAttributeSet::GetIncomingDamageAttribute(),
	                                                   EGameplayModOp::Additive, Damage);
	OutExecutionOutput.AddOutputModifier(EvaluatedData);
}
