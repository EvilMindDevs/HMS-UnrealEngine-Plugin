#pragma once

#include "HuaweiIapSettings.generated.h"

UCLASS(config = Engine, defaultconfig)
class UHuaweiIapSettings : public UObject
{
	GENERATED_UCLASS_BODY()

public:
	/* Path to agconnect-services.json */
	UPROPERTY(Config, EditAnywhere, Category = "HuaweiIAP")
	FString HuaweiAGCConfig;

	UPROPERTY(Config, EditAnywhere, Category = "HuaweiIAP")
	FString HuaweiIAPPublicKey;
};
