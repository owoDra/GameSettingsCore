// Copyright (C) 2023 owoDra

#pragma once

#include "Subsystems/Subsystem.h"

#include "GSCSubsystem.generated.h"


/**
 * Base class for auto instanced and initialized subsystem that share the lifetime of game user settings
 */
UCLASS(Abstract, Config = "GameUserSettings", configdonotcheckdefaults)
class GSCORE_API UGSCSubsystem : public UDynamicSubsystem
{
	GENERATED_BODY()

	friend class UGSCGameUserSettings;

public:
	UGSCSubsystem() {}

private:
	//
	// Name of the .ini file where the settings are stored
	//
	FString GSCSubsystemConfigIni;

protected:
	/**
	 * Loads the user .ini settings into GConfig
	 */
	virtual FString GetCustomConfigIniName() const;

	/** 
	 * Loads the user .ini settings into GConfig 
	 */
	void LoadConfigIni(bool bForceReload = false);

	virtual void LoadSettings(bool bForceReload = false);
	virtual void SaveSettings();

protected:
	virtual void SetToDefaults() {}
	virtual void ValidateSettings() {}
	virtual void ResetToCurrentSettings() {}
	virtual void ApplySettings() {}

	virtual bool IsDirty() const { return false; }

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

public:
	template<typename SettingsType = UGSCGameUserSettings>
	SettingsType* GetGameUserSettings() const
	{
		return Cast<SettingsType>(GetOuter());
	}

	template<typename SettingsType = UGSCGameUserSettings>
	SettingsType* GetGameUserSettingsChecked() const
	{
		return CastChecked<SettingsType>(GetOuter());
	}

};
