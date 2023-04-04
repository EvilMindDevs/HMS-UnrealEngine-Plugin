
#include "HuaweiAccountModule.h"
#include "HuaweiAccountSettings.h"
#include "Core.h"
#include "Modules/ModuleManager.h"

#include "Misc/ConfigCacheIni.h"
#include "UObject/Package.h"

#include "Developer/Settings/Public/ISettingsModule.h"

#define LOCTEXT_NAMESPACE "HuaweiAccountModule"

class HuaweiAccountModule : public IHuaweiAccountModule
{
    virtual void StartupModule() override
    {
        // This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
        Settings = NewObject<UHuaweiAccountSettings>(GetTransientPackage(), "HuaweiAccountSettings", RF_Standalone);
        Settings->AddToRoot();
        if (ISettingsModule *SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
        {
            SettingsModule->RegisterSettings("Project", "Plugins", "HuaweiAccount",
                                             LOCTEXT("HuaweiAccountSettingsName", "HuaweiAccount"),
                                             LOCTEXT("HuaweiAccountSettingsDescription", "Settings for Huawei Account"),
                                             Settings);
        }
    }

    virtual void ShutdownModule() override
    {
        // This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
        // we call this function before unloading the module.
        if (ISettingsModule *SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
        {
            SettingsModule->UnregisterSettings("Project", "Plugins", "HuaweiAccount");
        }

        if (!GExitPurge)
        {
            Settings->RemoveFromRoot();
        }
    }

private:
    UHuaweiAccountSettings *Settings;
};

IMPLEMENT_MODULE(HuaweiAccountModule, HuaweiAccount)

#undef LOCTEXT_NAMESPACE
