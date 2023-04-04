
#include "HuaweiIapModule.h"
#include "HuaweiIapSettings.h"
#include "Core.h"
#include "Modules/ModuleManager.h"

#include "Misc/ConfigCacheIni.h"
#include "UObject/Package.h"

#include "Developer/Settings/Public/ISettingsModule.h"

#define LOCTEXT_NAMESPACE "HuaweiIapModule"

class HuaweiIapModule : public IHuaweiIapModule
{
    virtual void StartupModule() override
    {
        // This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
        Settings = NewObject<UHuaweiIapSettings>(GetTransientPackage(), "HuaweiIapSettings", RF_Standalone);
        Settings->AddToRoot();
        if (ISettingsModule *SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
        {
            SettingsModule->RegisterSettings("Project", "Plugins", "HuaweiIAP",
                                             LOCTEXT("HuaweiIAPSettingsName", "HuaweiIAP"),
                                             LOCTEXT("HuaweiIAPSettingsDescription", "Settings for Huawei IAP"),
                                             Settings);
        }
    }

    virtual void ShutdownModule() override
    {
        // This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
        // we call this function before unloading the module.
        if (ISettingsModule *SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
        {
            SettingsModule->UnregisterSettings("Project", "Plugins", "HuaweiIAP");
        }

        if (!GExitPurge)
        {
            Settings->RemoveFromRoot();
        }
    }

private:
    UHuaweiIapSettings *Settings;
};

IMPLEMENT_MODULE(HuaweiIapModule, HuaweiIAP)

#undef LOCTEXT_NAMESPACE
