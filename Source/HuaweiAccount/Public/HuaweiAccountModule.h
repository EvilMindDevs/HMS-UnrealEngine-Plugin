#pragma once

#include "Modules/ModuleManager.h"

class IHuaweiAccountModule : public IModuleInterface
{
public:
	static inline IHuaweiAccountModule &Get()
	{
		return FModuleManager::LoadModuleChecked<IHuaweiAccountModule>("HuaweiAccountModule");
	}

	static inline bool IsAvailable()
	{
		return FModuleManager::Get().IsModuleLoaded("HuaweiAccountModule");
	}
};
