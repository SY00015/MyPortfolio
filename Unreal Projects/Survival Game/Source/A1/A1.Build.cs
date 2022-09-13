// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class A1 : ModuleRules
{
	public A1(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay","NavigationSystem", "GameplayTasks", "Niagara" });
        //		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay","NavigationSystem", "GameplayTasks", "Niagara" });

        PublicIncludePaths.AddRange(new string[] { "A1/",
            "C:/Program Files/Epic Games/UE_4.25/Engine/Plugins/FX/Niagara/Source/Niagara/Public",
            "C:/Program Files/Epic Games/UE_4.25/Engine/Plugins/FX/Niagara/Source/Niagara/Classes",
            "C:/Program Files/Epic Games/UE_4.25/Engine/Plugins/FX/Niagara/Source/Niagara/Private"});
    }
}
