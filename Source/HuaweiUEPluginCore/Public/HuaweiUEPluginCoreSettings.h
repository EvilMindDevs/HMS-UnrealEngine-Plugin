#pragma once

#include "HuaweiUEPluginCoreSettings.generated.h"

UCLASS(config = Engine, defaultconfig)
class UHuaweiUEPluginCoreSettings : public UObject
{
	GENERATED_UCLASS_BODY()

public:
	/* Path to agconnect-services.json */
	UPROPERTY(Config, EditAnywhere, Category = "HuaweiUEPluginCore")
	FString HuaweiAGCConfig;
};
