// Some copyright should be here...

using System;
using System.IO;
using UnrealBuildTool;
using UnrealBuildTool.Rules;

public class SpacetimeDbLib : ModuleRules
{
    
	public SpacetimeDbLib(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		// bEnableUndefinedIdentifierWarnings = false;

		PublicIncludePaths.AddRange(
        new string[]
        {
                @"$(ProjectDir)\Plugins\SpacetimeDbLib\Source\SpacetimeDbLib\include"
            }
		);


		PrivateIncludePaths.AddRange(
			new string[]
			{
                @"$(ProjectDir)\Plugins\SpacetimeDbLib\Source\SpacetimeDbLib\include"
            }
		);


		PublicSystemIncludePaths.AddRange(
			new string[]
			{
                @"$(ProjectDir)\Plugins\SpacetimeDbLib\Source\SpacetimeDbLib\include"
            }
		);


		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				// ... add other public dependencies that you statically link with here ...
			}
		);


		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				"Json",
				"JsonUtilities"
				// ... add private dependencies that you statically link with here ...	
			}
		);


		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
		);
	}
}