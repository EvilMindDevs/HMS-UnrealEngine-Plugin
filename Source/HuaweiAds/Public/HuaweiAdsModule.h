#pragma once

#include "Modules/ModuleManager.h"

class IHuaweiAdsModule : public IModuleInterface
{
public:
	static inline IHuaweiAdsModule &Get()
	{
		return FModuleManager::LoadModuleChecked<IHuaweiAdsModule>("HuaweiAdsModule");
	}

	static inline bool IsAvailable()
	{
		return FModuleManager::Get().IsModuleLoaded("HuaweiAdsModule");
	}
};
