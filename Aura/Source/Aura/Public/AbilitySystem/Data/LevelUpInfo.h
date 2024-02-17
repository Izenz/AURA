// Copyright Joel Herraiz.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "LevelUpInfo.generated.h"

USTRUCT(BlueprintType)
struct FAuraLevelUpInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	uint32 LevelUpRequirement = 0;

	UPROPERTY(EditDefaultsOnly)
	uint32 AttributePointAward = 1;

	UPROPERTY(EditDefaultsOnly)
	uint32 AbilityPointReward = 1;
};

/**
 * 
 */
UCLASS()
class AURA_API ULevelUpInfo : public UDataAsset
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditDefaultsOnly)
	TArray<FAuraLevelUpInfo> LevelUpInformation;

	uint32 GetLevelForExp(uint32 Exp) const;
};
