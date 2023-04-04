#include "HuaweiAccountSettings.h"

UHuaweiAccountSettings::UHuaweiAccountSettings(const FObjectInitializer &ObjectInitializer)
	: Super(ObjectInitializer), HuaweiAGCConfig(TEXT("Config/AGC/agconnect-services.json"))
{
}
