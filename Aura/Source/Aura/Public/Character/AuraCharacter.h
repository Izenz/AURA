// Copyright Joel Herraiz.

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "Interaction/PlayerInterface.h"
#include "AuraCharacter.generated.h"

class UNiagaraComponent;
class UCameraComponent;
class USpringArmComponent;
/**
 * 
 */
UCLASS()
class AURA_API AAuraCharacter : public AAuraCharacterBase, public IPlayerInterface
{
	GENERATED_BODY()
	
public:
	AAuraCharacter();

	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

	/** Combat Interface **/

	virtual int32 GetPlayerLevel_Implementation() const override;

	/** End Combat Interface **/

	/** Player Interface **/

	virtual void AddToExp_Implementation(int32 InExp) override;
	virtual int32 GetExp_Implementation() const override;
	virtual void LevelUp_Implementation() override;
	virtual int32 GetLevelForExp_Implementation(int32 Exp) const override;
	virtual int32 GetAttributePointsReward_Implementation(int32 Level) const override;
	virtual int32 GetAbilityPointsReward_Implementation(int32 Level) const override;
	virtual void AddToPlayerLevel_Implementation(int32 InPlayerLevel) override;
	virtual void AddToAttributePoints_Implementation(int32 InAttributePoints) override;
	virtual void AddToAbilityPoints_Implementation(int32 InAbilityPoints) override;
	virtual int32 GetAttributePoints_Implementation() const override;
	virtual int32 GetAbilityPoints_Implementation() const override;
	virtual ECharacterClass GetCharacterClass_Implementation() override;

	/** End Player Interface **/

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UNiagaraComponent> LevelUpNiagaraComponent;

private:

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCameraComponent> TopDownCameraComponent;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USpringArmComponent> CameraBoom;
	
	void InitAbilityActorInfo() override;

	UFUNCTION(NetMulticast, Reliable)
	void MulticastLevelUpParticles() const;
};
