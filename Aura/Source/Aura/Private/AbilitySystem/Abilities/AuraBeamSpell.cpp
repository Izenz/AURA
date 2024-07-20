// Copyright Joel Herraiz.


#include "AbilitySystem/Abilities/AuraBeamSpell.h"
#include "GameFramework/Character.h"
#include "Interaction/CombatInterface.h"
#include "Kismet/KismetSystemLibrary.h"

namespace
{
	constexpr float SPHERE_TRACE_RADIUS = 10.f;
}

void UAuraBeamSpell::StoreMouseDataInfo(const FHitResult HitResult)
{
	if (HitResult.bBlockingHit)
	{
		MouseHitLocation = HitResult.ImpactPoint;
		TargetActor = HitResult.GetActor();
	}
	else
	{
		CancelAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true);
	}
}

void UAuraBeamSpell::StoreOwnerParams()
{
	if (CurrentActorInfo)
	{
		OwnerPlayerController = CurrentActorInfo->PlayerController.Get();
		OwnerCharacter = Cast<ACharacter>(CurrentActorInfo->AvatarActor);
	}
}

void UAuraBeamSpell::TraceFrontmostTarget(const FVector& TargetLocation)
{
	check(OwnerCharacter);
	// TODO: use GetCombatSocketLocation
	if (OwnerCharacter->Implements<UCombatInterface>())
	{
		if (const USkeletalMeshComponent* Weapon = ICombatInterface::Execute_GetWeapon(OwnerCharacter))
		{
			const TArray<AActor*> ActorsToIgnore{OwnerCharacter};
			FHitResult HitResult;
			const FVector SocketLocation = Weapon->GetSocketLocation(FName("TipSocket"));
			UKismetSystemLibrary::SphereTraceSingle(OwnerCharacter, SocketLocation, TargetLocation, SPHERE_TRACE_RADIUS,
			                                        TraceTypeQuery1, false, ActorsToIgnore,
			                                        /*EDrawDebugTrace::ForDuration*/ EDrawDebugTrace::None, HitResult, true);

			if (HitResult.bBlockingHit)
			{
				MouseHitLocation = HitResult.ImpactPoint;
				TargetActor = HitResult.GetActor();
			}
		}
	}
}
