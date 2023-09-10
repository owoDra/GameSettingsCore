﻿// Copyright (C) 2023 owoDra

#include "GSEditorCore.h"

#include "Definition/Picker/GSCPicker_DataSource.h"
#include "PropertyCustomization/GSCDataSourcePickerCustomization.h"

#include "PropertyCustomization/GSCSettingSourcePickerCustomization.h"
#include "PropertyCustomization/GSCPropertySourcePickerCustomization.h"

IMPLEMENT_MODULE(FGSEditorCoreModule, GSEditorCore)


void FGSEditorCoreModule::StartupModule()
{
	RegisterPropertyCustomizations();
}

void FGSEditorCoreModule::ShutdownModule()
{
	UnregisterPropertyCustomizations();
}


void FGSEditorCoreModule::RegisterPropertyCustomizations()
{
	if (!FModuleManager::Get().IsModuleLoaded(NAME_PropertyEditorModule))
	{
		return;
	}

	auto& PropertyModule{ FModuleManager::LoadModuleChecked<FPropertyEditorModule>(NAME_PropertyEditorModule) };

	PropertyModule.RegisterCustomPropertyTypeLayout(
		FGSCPicker_DataSource::StaticStruct()->GetFName(),
		FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FGSCDataSourcePickerCustomization::MakeInstance));

	FGSCSettingSourcePickerCustomization::RegisterToPropertyEditorModule(PropertyModule);
	FGSCPropertySourcePickerCustomization::RegisterToPropertyEditorModule(PropertyModule);

	PropertyModule.NotifyCustomizationModuleChanged();
}

void FGSEditorCoreModule::UnregisterPropertyCustomizations()
{
	if (!FModuleManager::Get().IsModuleLoaded(NAME_PropertyEditorModule))
	{
		return;
	}

	auto& PropertyModule{ FModuleManager::LoadModuleChecked<FPropertyEditorModule>(NAME_PropertyEditorModule) };

	PropertyModule.UnregisterCustomPropertyTypeLayout(FGSCPicker_DataSource::StaticStruct()->GetFName());

	FGSCSettingSourcePickerCustomization::UnregisterToPropertyEditorModule(PropertyModule);
	FGSCPropertySourcePickerCustomization::UnregisterToPropertyEditorModule(PropertyModule);
}