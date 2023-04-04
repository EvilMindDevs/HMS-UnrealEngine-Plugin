
#include "HuaweiAdsModule.h"
#include "HuaweiAdsSettings.h"
#include "Core.h"
#include "Modules/ModuleManager.h"

#include "Misc/ConfigCacheIni.h"
#include "UObject/Package.h"

#include "Developer/Settings/Public/ISettingsModule.h"

#define LOCTEXT_NAMESPACE "HuaweiAdsModule"

class HuaweiAdsModule : public IHuaweiAdsModule
{
    virtual void StartupModule() override
    {
        // This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
        Settings = NewObject<UHuaweiAdsSettings>(GetTransientPackage(), "HuaweiAdsSettings", RF_Standalone);
        Settings->AddToRoot();
        if (ISettingsModule *SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
        {
            SettingsModule->RegisterSettings("Project", "Plugins", "HuaweiAds",
                                             LOCTEXT("HuaweiAdsSettingsName", "HuaweiAds"),
                                             LOCTEXT("HuaweiAdsSettingsDescription", "Settings for Huawei Ads"),
                                             Settings);
        }
    }

    virtual void ShutdownModule() override
    {
        // This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
        // we call this function before unloading the module.
        if (ISettingsModule *SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
        {
            SettingsModule->UnregisterSettings("Project", "Plugins", "HuaweiAds");
        }

        if (!GExitPurge)
        {
            Settings->RemoveFromRoot();
        }
    }

private:
    UHuaweiAdsSettings *Settings;
};

IMPLEMENT_MODULE(HuaweiAdsModule, HuaweiAds)

#undef LOCTEXT_NAMESPACE
