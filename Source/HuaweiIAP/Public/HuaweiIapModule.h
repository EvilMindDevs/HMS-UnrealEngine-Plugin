#pragma once

#include "Modules/ModuleManager.h"

class IHuaweiIapModule : public IModuleInterface
{
public:
	static inline IHuaweiIapModule &Get()
	{
		return FModuleManager::LoadModuleChecked<IHuaweiIapModule>("HuaweiIapModule");
	}

	static inline bool IsAvailable()
	{
		return FModuleManager::Get().IsModuleLoaded("HuaweiIapModule");
	}
};