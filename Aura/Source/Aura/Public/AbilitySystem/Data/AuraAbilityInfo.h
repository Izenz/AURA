// Copyright Joel Herraiz.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "AuraAbilityInfo.generated.h"

USTRUCT(BlueprintType)
struct FAbilityInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag AbilityTag = FGameplayTag();

	UPROPERTY(BlueprintReadOnly)
	FGameplayTag InputTag = FGameplayTag();

	UPROPERTY(BlueprintReadOnly)
	FGameplayTag StatusTag = FGameplayTag();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag CooldownTag = FGameplayTag();
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<const UTexture2D> Icon = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<const UMaterialInterface> BgMaterial = nullptr;
};

/**
 * 
 */
UCLASS()
class AURA_API UAuraAbilityInfo : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AbilityInformation")
	TArray<FAbilityInfo> AbilityInformation;

	FAbilityInfo FindAbilityInfoForTag(const FGameplayTag& GameplayTag, bool bLogIfNotFound = false) const;
};
