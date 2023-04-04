using System.IO;

using Tools.DotNETCommon;

using UnrealBuildTool;

public class HuaweiAccount : ModuleRules
{
    public HuaweiAccount(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PrivateIncludePaths.AddRange(
                new string[] {
                    "HuaweiAccount/Private"
                });

        PublicDependencyModuleNames.AddRange(
            new string[] {
                "Core",
                "CoreUObject",
                "Engine",
                "RenderCore",
                "RHI"
            });

        PrivateIncludePathModuleNames.AddRange(
            new string[] {
                "Settings",
                "Launch"
            }
        );

        if (Target.Platform == UnrealTargetPlatform.Android)
        {
            PublicDependencyModuleNames.AddRange(
                new string[]
                {
                    "Launch"
                })
            ;
            string PluginPath = Utils.MakePathRelativeTo(ModuleDirectory, Target.RelativeEnginePath);
            AdditionalPropertiesForReceipt.Add(new ReceiptProperty("AndroidPlugin", Path.Combine(PluginPath, "HuaweiAccount_APL.xml")));
        }
    }
}
