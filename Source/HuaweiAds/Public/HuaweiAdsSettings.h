#pragma once

#include "HuaweiAdsSettings.generated.h"

UCLASS(config = Engine, defaultconfig)
class UHuaweiAdsSettings : public UObject
{
	GENERATED_UCLASS_BODY()

public:
	/* Path to agconnect-services.json */
	UPROPERTY(Config, EditAnywhere, Category = "HuaweiAds")
	FString HuaweiAGCConfig;
};
