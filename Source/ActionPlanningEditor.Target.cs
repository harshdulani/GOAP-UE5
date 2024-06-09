// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class ActionPlanningEditorTarget : TargetRules
{
	public ActionPlanningEditorTarget(TargetInfo Target) : base(Target)
	{
		bOverrideBuildEnvironment = true;
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V5;
		IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
		ExtraModuleNames.Add("ActionPlanning");
	}
}
