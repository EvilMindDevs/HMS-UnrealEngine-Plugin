// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Modules/ModuleManager.h"

class IHuaweiUEPluginCoreModule : public IModuleInterface
{
public:
	static inline IHuaweiUEPluginCoreModule &Get()
	{
		return FModuleManager::LoadModuleChecked<IHuaweiUEPluginCoreModule>("HuaweiUEPluginCoreModule");
	}

	static inline bool IsAvailable()
	{
		return FModuleManager::Get().IsModuleLoaded("HuaweiUEPluginCoreModule");
	}
};
