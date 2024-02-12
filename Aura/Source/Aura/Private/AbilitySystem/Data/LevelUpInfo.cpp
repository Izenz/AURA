// Copyright Joel Herraiz.


#include "AbilitySystem/Data/LevelUpInfo.h"

uint32 ULevelUpInfo::GetLevelForExp(uint32 Exp) const
{
	int Level = 1;
	bool bSearching = true;

	while (bSearching)
	{
		if (LevelUpInformation.Num() <= Level)	return Level;
		
		if (Exp >= LevelUpInformation[Level].LevelUpRequirement)
		{
			++Level;
		}
		else
		{
			bSearching = false;
		}
	}
	
	return Level;
}
