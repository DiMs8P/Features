// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Features : ModuleRules
{
	public Features(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "GameplayAbilities" });
	}
}
