// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class DancysGame : ModuleRules
{
	public DancysGame(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
