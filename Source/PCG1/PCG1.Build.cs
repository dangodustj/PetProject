// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class PCG1 : ModuleRules
{
	public PCG1(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate",
			"GameplayAbilities",
			"GameplayTasks",
			"GameplayTags",
			"GameplayMessageRuntime"
		});

		PublicIncludePaths.AddRange(new string[] {
			"PCG1",
			"PCG1/Variant_Platforming",
			"PCG1/Variant_Platforming/Animation",
			"PCG1/Variant_Combat",
			"PCG1/Variant_Combat/AI",
			"PCG1/Variant_Combat/Animation",
			"PCG1/Variant_Combat/Gameplay",
			"PCG1/Variant_Combat/Interfaces",
			"PCG1/Variant_Combat/UI",
			"PCG1/Variant_SideScrolling",
			"PCG1/Variant_SideScrolling/AI",
			"PCG1/Variant_SideScrolling/Gameplay",
			"PCG1/Variant_SideScrolling/Interfaces",
			"PCG1/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
