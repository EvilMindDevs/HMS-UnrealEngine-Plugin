// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Modules/ModuleManager.h"

class IHuaweiPushModule : public IModuleInterface
{
public:
	static inline IHuaweiPushModule &Get()
	{
		return FModuleManager::LoadModuleChecked<IHuaweiPushModule>("HuaweiPushModule");
	}

	static inline bool IsAvailable()
	{
		return FModuleManager::Get().IsModuleLoaded("HuaweiPushModule");
	}
};
