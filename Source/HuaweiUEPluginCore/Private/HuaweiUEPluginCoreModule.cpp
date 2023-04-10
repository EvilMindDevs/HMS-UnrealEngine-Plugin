
#include "HuaweiUEPluginCoreModule.h"
#include "HuaweiUEPluginCoreSettings.h"
#include "Core.h"
#include "Modules/ModuleManager.h"

#include "Misc/ConfigCacheIni.h"
#include "UObject/Package.h"

#include "Developer/Settings/Public/ISettingsModule.h"

#define LOCTEXT_NAMESPACE "HuaweiUEPluginCoreModule"

class HuaweiUEPluginCoreModule : public IHuaweiUEPluginCoreModule
{
	virtual void StartupModule() override
	{
		// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
		Settings = NewObject<UHuaweiUEPluginCoreSettings>(GetTransientPackage(), "HuaweiUEPluginCoreSettings", RF_Standalone);
		Settings->AddToRoot();
		if (ISettingsModule *SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
		{
			SettingsModule->RegisterSettings("Project", "Plugins", "HuaweiUEPluginCore",
				LOCTEXT("HuaweiUEPluginCoreSettingsName", "HuaweiUEPluginCore"),
				LOCTEXT("HuaweiUEPluginCoreSettingsDescription", "Settings for Huawei Push"),
				Settings);
		}
	}

	virtual void ShutdownModule() override
	{
		// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
		// we call this function before unloading the module.
		if (ISettingsModule *SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
		{
			SettingsModule->UnregisterSettings("Project", "Plugins", "HuaweiUEPluginCore");
		}

		if (!GExitPurge)
		{
			Settings->RemoveFromRoot();
		}
	}

private:
	UHuaweiUEPluginCoreSettings *Settings;
};

IMPLEMENT_MODULE(HuaweiUEPluginCoreModule, HuaweiUEPluginCore)

#undef LOCTEXT_NAMESPACE
