// Copyright Joel Herraiz.

#include "AbilitySystem/Abilities/AuraFireBolt.h"

#include "Interaction/CombatInterface.h"
#include "Kismet/KismetSystemLibrary.h"

FString UAuraFireBolt::GetDescription(int32 Level)
{
	const float SkillDamage = Damage.GetValueAtLevel(Level); 
	const float ManaCost = FMath::Abs(GetManaCost(Level));
	const float Cooldown = GetCooldown(Level);
	
	return FString::Printf(TEXT("<Title>FIRE BOLT Lv %d</>\n\n"
			"<Default>Mana Cost: </><ManaCost>%.2f</>\n"
			"<Default>Cooldown: </><Cooldown>%.2f</><Default> seconds.</>\n\n"
			"<Default>Launches </><Enhancement>%d</><Default> bolts of fire, exploding on impact and dealing </><Damage>%d</>"
			"<Default> fire damage with a chance to burn.</>"), Level, ManaCost, Cooldown, FMath::Min(Level, NumOfProjectiles), SkillDamage);
}

FString UAuraFireBolt::GetNextLevelDescription(int32 Level)
{
	return GetDescription(Level);
}

void UAuraFireBolt::SpawnProjectiles(const FVector& ProjectileTargetLocation, const FGameplayTag& SocketTag,
	bool bOverridePitch, float PitchOverride, AActor* HomingTarget)
{
	const bool bIsServer = GetAvatarActorFromActorInfo()->HasAuthority();
	if (!bIsServer) return;

	const FVector SocketLocation = ICombatInterface::Execute_GetCombatSocketLocation(GetAvatarActorFromActorInfo(), SocketTag);
	FRotator Rotation = (ProjectileTargetLocation - SocketLocation).Rotation();
	if (bOverridePitch) Rotation.Pitch = PitchOverride;

	const FVector Forward = Rotation.Vector();
	const FVector LeftOfSpread = Forward.RotateAngleAxis(-ProjectileSpread / 2.f, FVector::UpVector);
	const FVector RightOfSpread = Forward.RotateAngleAxis(ProjectileSpread / 2.f, FVector::UpVector);
	const FVector Start = SocketLocation + FVector(0, 0, 5);
	constexpr float Length = 75.f;

	if (NumOfProjectiles > 1)
	{
		const float DeltaSpread = ProjectileSpread / (NumOfProjectiles - 1);
		for (int32 i = 0; i < NumOfProjectiles; ++i)
		{
			const FVector Direction = LeftOfSpread.RotateAngleAxis(DeltaSpread * i, FVector::UpVector);
			UKismetSystemLibrary::DrawDebugArrow(GetAvatarActorFromActorInfo(), Start, Start + Direction * Length, 1, FLinearColor::Red, 120, 1);
		}
	}
	else
	{
		UKismetSystemLibrary::DrawDebugArrow(GetAvatarActorFromActorInfo(), Start, Start + Forward * Length, 1, FLinearColor::Red, 120, 1);
	}
	
	UKismetSystemLibrary::DrawDebugArrow(GetAvatarActorFromActorInfo(), SocketLocation, SocketLocation + Forward * 100.f, 1, FLinearColor::White, 120, 1);
	UKismetSystemLibrary::DrawDebugArrow(GetAvatarActorFromActorInfo(), SocketLocation, SocketLocation + LeftOfSpread * 100.f, 1, FLinearColor::Gray, 120, 1);
	UKismetSystemLibrary::DrawDebugArrow(GetAvatarActorFromActorInfo(), SocketLocation, SocketLocation + RightOfSpread * 100.f, 1, FLinearColor::Gray, 120, 1);
}
