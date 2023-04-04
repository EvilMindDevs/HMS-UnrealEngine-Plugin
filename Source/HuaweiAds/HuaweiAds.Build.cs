using System.IO;
using Tools.DotNETCommon;
using UnrealBuildTool;

public class HuaweiAds : ModuleRules
{
	public HuaweiAds(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PrivateIncludePaths.AddRange(
                new string[] {
                    "HuaweiAds/Private"
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

		if(Target.Platform == UnrealTargetPlatform.Android)
		{
			PublicDependencyModuleNames.AddRange(
				new string[]
				{
					"Launch"
				})
			;
			string PluginPath = Utils.MakePathRelativeTo(ModuleDirectory, Target.RelativeEnginePath);
			AdditionalPropertiesForReceipt.Add(new ReceiptProperty("AndroidPlugin", Path.Combine(PluginPath, "HuaweiAds_APL.xml")));
		}
	}
}
