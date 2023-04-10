using System.IO;
using Tools.DotNETCommon;
using UnrealBuildTool;

namespace UnrealBuildTool.Rules
{
    public class HuaweiUEPluginCore : ModuleRules
    {
        public HuaweiUEPluginCore(ReadOnlyTargetRules Target) : base(Target)
        {
            PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
            PrivateIncludePaths.AddRange(
                new string[] {
                    "HuaweiUEPluginCore/Private"
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
                AdditionalPropertiesForReceipt.Add(new ReceiptProperty("AndroidPlugin", Path.Combine(PluginPath, "HuaweiUEPluginCore_APL.xml")));
            }
        }
    }
}