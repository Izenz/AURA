// Copyright Joel Herraiz.

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include "AbilityMenuWidgetController.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAbilityMenuWidgetController : public UAuraWidgetController
{
	GENERATED_BODY()
public:
	virtual void BroadcastInitialValue() override;
	virtual void BindCallbacksToDependencies() override;
};
