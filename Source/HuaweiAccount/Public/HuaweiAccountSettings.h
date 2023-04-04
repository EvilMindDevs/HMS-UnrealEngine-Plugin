#pragma once

#include "HuaweiAccountSettings.generated.h"

UCLASS(config = Engine, defaultconfig)
class UHuaweiAccountSettings : public UObject
{
	GENERATED_UCLASS_BODY()

public:
	/* Path to agconnect-services.json */
	UPROPERTY(Config, EditAnywhere, Category = "HuaweiAccount")
	FString HuaweiAGCConfig;
};
