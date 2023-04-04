#include "HuaweiPushSettings.h"

UHuaweiPushSettings::UHuaweiPushSettings(const FObjectInitializer &ObjectInitializer)
	: Super(ObjectInitializer), HuaweiAGCConfig(TEXT("Config/AGC/agconnect-services.json"))
{
}
