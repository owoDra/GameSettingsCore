﻿// Copyright (C) 2023 owoDra

#include "GSCGameUserSettings.h"

#include "GSCSubsystem.h"
#include "GSCoreLogs.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(GSCGameUserSettings)


UGSCGameUserSettings::UGSCGameUserSettings(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	SetToDefaults();
}


void UGSCGameUserSettings::InitializeSubsystems()
{
	UE_LOG(LogGSC, Log, TEXT("=== Initializing GameUserSettings(%s) ==="), *GetNameSafe(this));

	SubsystemCollection.Initialize(this);
}

void UGSCGameUserSettings::DeinitializeSubsystems()
{
	SubsystemCollection.Deinitialize();
}

void UGSCGameUserSettings::PostInitProperties()
{
	InitializeSubsystems();

	Super::PostInitProperties();
}

void UGSCGameUserSettings::BeginDestroy()
{
	DeinitializeSubsystems();

	Super::BeginDestroy();
}


void UGSCGameUserSettings::SetToDefaults()
{
	Super::SetToDefaults();

	for (const auto& Each : GetSubsystemArray())
	{
		Each->SetToDefaults();
	}
}

void UGSCGameUserSettings::LoadSettings(bool bForceReload)
{
	Super::LoadSettings(bForceReload);

	for (const auto& Each : GetSubsystemArray())
	{
		Each->LoadSettings(bForceReload);
	}
}

void UGSCGameUserSettings::ValidateSettings()
{
	Super::ValidateSettings();

	for (const auto& Each : GetSubsystemArray())
	{
		Each->ValidateSettings();
	}
}

void UGSCGameUserSettings::SaveSettings()
{
	Super::SaveSettings();

	for (const auto& Each : GetSubsystemArray())
	{
		Each->SaveSettings();
	}
}

void UGSCGameUserSettings::ApplySettings(bool bCheckForCommandLineOverrides)
{
	for (const auto& Each : GetSubsystemArray())
	{
		Each->ApplySettings();
	}

	Super::ApplySettings(bCheckForCommandLineOverrides);
}

void UGSCGameUserSettings::ResetToCurrentSettings()
{
	Super::ResetToCurrentSettings();

	for (const auto& Each : GetSubsystemArray())
	{
		Each->ResetToCurrentSettings();
	}
}

bool UGSCGameUserSettings::IsDirty() const
{
	QUICK_SCOPE_CYCLE_COUNTER(GSCGameUserSettings_IsDirty);

	// Skip process if already dirty

	if (Super::IsDirty())
	{
		return true;
	}

	// Verify all subsystems

	for (const auto& Each : GetSubsystemArray())
	{
		if (Each->IsDirty())
		{
			return true;
		}
	}

	return false;
}

bool UGSCGameUserSettings::IsDirtyIgnoreSubsystems() const
{
	return Super::IsDirty();
}