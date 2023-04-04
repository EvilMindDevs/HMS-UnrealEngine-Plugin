#include "HuaweiIapSettings.h"

UHuaweiIapSettings::UHuaweiIapSettings(const FObjectInitializer &ObjectInitializer)
	: Super(ObjectInitializer), HuaweiAGCConfig(TEXT("Config/AGC/agconnect-services.json")), HuaweiIAPPublicKey(TEXT(""))
{
}
