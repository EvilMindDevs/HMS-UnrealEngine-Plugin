#pragma once

#include "HuaweiPushSettings.generated.h"

UCLASS(config = Engine, defaultconfig)
class UHuaweiPushSettings : public UObject
{
	GENERATED_UCLASS_BODY()

public:
	/* Path to agconnect-services.json */
	UPROPERTY(Config, EditAnywhere, Category = "HuaweiPush")
	FString HuaweiAGCConfig;
};
