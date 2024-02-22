// Copyright Joel Herraiz.

#pragma once

#include "CoreMinimal.h"
#include "AuraWidgetController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerStatChangedSignature, int32, NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAbilityInfoSignature, const FAbilityInfo&, Info);

class UAbilitySystemComponent;
class UAttributeSet;
class UAuraAbilityInfo;

USTRUCT(BlueprintType)
struct FWidgetControllerParams
{
	GENERATED_BODY()

	FWidgetControllerParams() {}
	FWidgetControllerParams(APlayerController* PC, APlayerState* PS,
		UAbilitySystemComponent* ASC, UAttributeSet* AS) : 
		PlayerController(PC), PlayerState(PS), AbilitySystemComponent(ASC), AttributeSet(AS) {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<APlayerController> PlayerController = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<APlayerState> PlayerState = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UAttributeSet> AttributeSet = nullptr;
};

/**
 * 
 */
UCLASS()
class AURA_API UAuraWidgetController : public UObject
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void SetWidgetControllerParams(const FWidgetControllerParams& WCParams);

	UFUNCTION(BlueprintCallable)
	virtual void BroadcastInitialValue();
	virtual void BindCallbacksToDependencies();

	UPROPERTY(BlueprintAssignable, Category = "GAS|Messages")
	FAbilityInfoSignature AbilityInfoDelegate;

	void BroadcastAbilityInfo();

	template <typename T>
	T* GetPlayerController()
	{
		if (auto Controller = CastChecked<T>(PlayerController))
		{
			return Controller;
		}
		
		throw std::exception("Can not convert PlayerController to specified type.");
	}

	template <typename T>
	T* GetPlayerState()
	{
		if (auto AuraPlayerState = CastChecked<T>(PlayerState))
		{
			return AuraPlayerState;
		}
		
		throw std::exception("Can not convert PlayerState to specified type.");
	}

	template <typename T>
	T* GetAbilitySystemComponent()
	{
		if (auto Asc = CastChecked<T>(AbilitySystemComponent))
		{
			return Asc;
		}
		
		throw std::exception("Can not convert AbilitySystemComponent to specified type.");
	}

	template <typename T>
	T* GetAttributeSet()
	{
		if (auto AttSet = CastChecked<T>(AttributeSet))
		{
			return AttSet;
		}
		
		throw std::exception("Can not convert AttributeSet to specified type.");
	}

protected:

	// The main variables the controller will get data from to broadcast to Widgets.

	UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
	TObjectPtr<APlayerController> PlayerController;

	UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
	TObjectPtr<APlayerState> PlayerState;

	UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
	TObjectPtr<UAttributeSet> AttributeSet;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Widget Data")
	TObjectPtr<UAuraAbilityInfo> AbilityInfo;
};
